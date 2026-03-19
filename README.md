# Ugar.io Qt
[![Build Desktop Binaries](https://github.com/ShortKedr/ugar-io-qt/actions/workflows/build-desktop.yml/badge.svg)](https://github.com/ShortKedr/ugar-io-qt/actions/workflows/build-desktop.yml)

Simple single-player Agar.io-style game built with C++20, Qt, and OpenGL-backed rendering.

This repository is the Qt implementation. The GLFW/OpenGL version lives here: [ShortKedr/ugar-io-opengl](https://github.com/ShortKedr/ugar-io-opengl).

## Gameplay
[![Gameplay preview](docs/ugario_gameplay.gif)](docs/ugario_gameplay.mov)

Add `docs/ugario_gameplay.gif` and `docs/ugario_gameplay.mov` to publish the preview in the repository README.

## Controls
- `Space` starts a round
- `W`, `A`, `S`, `D` move the player blob

## Project Layout
- `src/` contains implementation files
- `include/ugar_io_qt/` contains project headers
- `resources/` contains the app icons, `qt.conf`, and the Windows resource script
- `scripts/package-appimage.sh` builds a Linux AppImage from an existing release build
- `docs/` is the intended home for README preview assets such as the gameplay GIF and video
- `.github/workflows/build-desktop.yml` builds and packages Windows, Linux, and macOS artifacts
- `CMakeLists.txt` is the primary build entrypoint

## Requirements
1. CMake 3.21 or newer
2. A C++20-capable compiler toolchain
3. Qt 6 with `Core`, `Gui`, and `OpenGL`
4. `windeployqt` on Windows, `macdeployqt` on macOS, or the AppImage prerequisites used by `scripts/package-appimage.sh` on Linux
5. On Windows: start from a shell where your compiler and Qt are already available in `PATH`, or pass `CMAKE_PREFIX_PATH` explicitly

## Build
The project now uses the same two-step build flow everywhere:

```bash
cmake -S . -B build/<platform>-release -DCMAKE_BUILD_TYPE=Release
cmake --build build/<platform>-release
```

Deploy or packaging is an explicit third step per platform.

### Windows
Start from a shell where Qt and your compiler toolchain are already configured. One simple option is to expose your Qt and MinGW installations through environment variables:

```powershell
$env:QT_ROOT="path\to\Qt\6.x\mingw_64"
$env:MINGW_ROOT="path\to\Qt\Tools\mingwXXXX_64"
$env:PATH="$env:MINGW_ROOT\bin;$env:QT_ROOT\bin;$env:PATH"
```

Then configure, build, and deploy:

```powershell
cmake -S . -B build/windows-release -G Ninja `
  -DCMAKE_BUILD_TYPE=Release `
  -DCMAKE_PREFIX_PATH="$env:QT_ROOT"

cmake --build build/windows-release
windeployqt build/windows-release/ugar-io-qt.exe
```

If you want to stage a distributable folder, copy the resulting `.exe`, `qt.conf`, and deployed Qt files into a `dist/` directory after `windeployqt`.

### macOS
Install Qt 6, then run:

```bash
cmake -S . -B build/macos-release -DCMAKE_BUILD_TYPE=Release
cmake --build build/macos-release
macdeployqt build/macos-release/ugar-io-qt.app
```

### Linux
Install Qt 6 and build dependencies, then run:

```bash
cmake -S . -B build/linux-release -DCMAKE_BUILD_TYPE=Release
cmake --build build/linux-release
./scripts/package-appimage.sh build/linux-release
```

The AppImage script runs `cmake --install` into `AppDir/usr`, adds `resources/icon.png`, writes an `AppRun` launcher for the deployed Qt layout, and emits `build/linux-release/ugar-io-qt-linux-x86_64.AppImage`.

## CI and Releases
GitHub Actions builds desktop artifacts for Windows, Linux, and macOS using the same `configure -> build -> deploy/package` flow as local development. Tagged releases upload a Windows ZIP, a Linux `AppImage`, and a macOS ZIP.

## CLion
Recommended Windows setup:
- Toolchain uses your Qt-compatible `gcc`, `g++`, and `gdb`
- CMake uses the `cmake` executable available in your environment
- Build tool uses `ninja` from your environment
- Environment provides `QT_ROOT=path\to\Qt\6.x\mingw_64`
- Environment provides `MINGW_ROOT=path\to\Qt\Tools\mingwXXXX_64`
- Configure with `-DCMAKE_PREFIX_PATH=%QT_ROOT%` and build into `build/windows-release`
