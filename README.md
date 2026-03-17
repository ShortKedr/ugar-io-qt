# Ugar.io Qt
[![Build Desktop Binaries](https://github.com/ShortKedr/ugar-io-qt/actions/workflows/build-desktop.yml/badge.svg)](https://github.com/ShortKedr/ugar-io-qt/actions/workflows/build-desktop.yml)

Simplest single-player copy of Agar.io game, made with C++ and Qt.

This project has another implementation with OpenGL: [watch here](https://github.com/ShortKedr/ugar-io-opengl).

## Project Layout
- `src/` contains implementation files
- `include/ugar_io_qt/` contains project headers
- `resources/` contains Windows resource files and deployment metadata
- `CMakeLists.txt` is the primary build entrypoint

## Requirements
1. CMake 3.21 or newer
1. A C++20-capable compiler toolchain
1. Qt 6 for CI builds, or Qt 5/Qt 6 installed locally for manual builds
1. Qt Core and Qt Gui development packages for your platform

## Configure and Build
Windows, Linux, macOS:

```bash
cmake -S . -B build
cmake --build build
```

The project now uses CMake as the primary build system and keeps compatibility with both Qt 6 and Qt 5 for local development.

## Windows with Qt6 + MinGW
If you install Qt in the `MinGW 64-bit` variant, this repository is ready to use it through CMake presets.

Set two environment variables before opening CLion or running CMake:

```powershell
$env:QT_ROOT="C:\Qt\6.7.3\mingw_64"
$env:MINGW_ROOT="C:\Qt\Tools\mingw1310_64"
```

Then configure and build with:

```bash
cmake --preset windows-mingw-debug
cmake --build --preset build-windows-mingw-debug
```

In CLion, reload the project and select the `Windows MinGW Debug` or `Windows MinGW Release` preset instead of the default Visual Studio toolchain.
