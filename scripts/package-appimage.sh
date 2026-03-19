#!/usr/bin/env bash

set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <build-dir>" >&2
  exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="$(cd "$1" && pwd)"
APP_NAME="ugar-io-qt"
APPDIR="${BUILD_DIR}/AppDir"
INSTALL_ROOT="${APPDIR}/usr"
APPIMAGE="${BUILD_DIR}/${APP_NAME}-linux-x86_64.AppImage"
APP_BINARY="${BUILD_DIR}/${APP_NAME}"
DESKTOP_FILE="${APPDIR}/${APP_NAME}.desktop"
ICON_FILE="${APPDIR}/${APP_NAME}.png"
ICON_SOURCE="${REPO_ROOT}/resources/icon.png"
DESKTOP_TEMPLATE="${REPO_ROOT}/resources/${APP_NAME}.desktop.in"
APPIMAGETOOL_APPIMAGE="${BUILD_DIR}/appimagetool-x86_64.AppImage"

if [[ ! -x "${APP_BINARY}" ]]; then
  echo "Expected built binary at ${APP_BINARY}" >&2
  exit 1
fi

if [[ ! -f "${DESKTOP_TEMPLATE}" ]]; then
  echo "Missing desktop template: ${DESKTOP_TEMPLATE}" >&2
  exit 1
fi

if [[ ! -f "${ICON_SOURCE}" ]]; then
  echo "Missing app icon: ${ICON_SOURCE}" >&2
  exit 1
fi

for tool in cmake wget; do
  if ! command -v "${tool}" >/dev/null 2>&1; then
    echo "Missing required tool: ${tool}" >&2
    exit 1
  fi
done

rm -rf "${APPDIR}" "${APPIMAGE}"
mkdir -p "${APPDIR}/usr/bin" "${APPDIR}/usr/share/applications" "${APPDIR}/usr/share/icons/hicolor/256x256/apps"

cmake --install "${BUILD_DIR}" --prefix "${INSTALL_ROOT}"

if [[ ! -x "${INSTALL_ROOT}/bin/${APP_NAME}" ]]; then
  echo "Expected installed binary at ${INSTALL_ROOT}/bin/${APP_NAME}" >&2
  exit 1
fi

sed "s|@UGAR_IO_QT_APP_ID@|${APP_NAME}|g" "${DESKTOP_TEMPLATE}" > "${APPDIR}/usr/share/applications/${APP_NAME}.desktop"
cp "${APPDIR}/usr/share/applications/${APP_NAME}.desktop" "${DESKTOP_FILE}"
cp "${ICON_SOURCE}" "${ICON_FILE}"
cp "${ICON_FILE}" "${APPDIR}/usr/share/icons/hicolor/256x256/apps/${APP_NAME}.png"
ln -s usr/bin/${APP_NAME} "${APPDIR}/AppRun"

if [[ ! -f "${APPIMAGETOOL_APPIMAGE}" ]]; then
  wget -q "https://github.com/AppImage/AppImageKit/releases/download/continuous/appimagetool-x86_64.AppImage" -O "${APPIMAGETOOL_APPIMAGE}"
  chmod +x "${APPIMAGETOOL_APPIMAGE}"
fi

export VERSION="${VERSION:-continuous}"
export ARCH="${ARCH:-x86_64}"
APPIMAGE_EXTRACT_AND_RUN=1 ARCH="${ARCH}" "${APPIMAGETOOL_APPIMAGE}" "${APPDIR}" "${APPIMAGE}"

if [[ ! -f "${APPIMAGE}" ]]; then
  echo "appimagetool did not produce ${APPIMAGE}" >&2
  exit 1
fi
