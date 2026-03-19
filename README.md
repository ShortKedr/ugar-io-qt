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
- `resources/` contains the app icon, `qt.conf`, and the Windows resource script
- `cmake/toolchains/qt6-mingw.cmake` configures the Windows Qt + MinGW toolchain
- `docs/` is the intended home for README preview assets such as the gameplay GIF and video
- `.github/workflows/build-desktop.yml` builds and packages Windows, Linux, and macOS artifacts
- `CMakeLists.txt` is the primary build entrypoint
- `CMakePresets.json` contains ready-to-use Windows MinGW presets

## Requirements
1. CMake 3.21 or newer
2. A C++20-capable compiler toolchain
3. Qt 6 with `Core`, `Gui`, and `OpenGL`
4. Ninja is recommended for local builds
5. On Windows preset builds: Qt `MinGW 64-bit`, MinGW, CMake, and Ninja from the Qt installer

## Build
### Windows with Qt + MinGW presets
This is the main local development setup for the repository.

Set these environment variables before running CMake:

```powershell
$env:QT_ROOT="C:\Qt\6.10.2\mingw_64"
$env:MINGW_ROOT="C:\Qt\Tools\mingw1310_64"
```

Configure and build a debug build:

```powershell
C:\Qt\Tools\CMake_64\bin\cmake.exe --preset windows-mingw-debug
C:\Qt\Tools\CMake_64\bin\cmake.exe --build --preset build-windows-mingw-debug
```

Configure and build a release build:

```powershell
C:\Qt\Tools\CMake_64\bin\cmake.exe --preset windows-mingw-release
C:\Qt\Tools\CMake_64\bin\cmake.exe --build --preset build-windows-mingw-release
```

Produced binaries:
- `build/windows-mingw-debug/ugar-io-qt.exe`
- `build/windows-mingw-release/ugar-io-qt.exe`

### Windows with manual CMake arguments
If you prefer not to use presets, point CMake at the same toolchain file directly:

```powershell
C:\Qt\Tools\CMake_64\bin\cmake.exe -S . -B build/manual-mingw-debug -G Ninja `
  -DCMAKE_BUILD_TYPE=Debug `
  -DCMAKE_MAKE_PROGRAM=C:/Qt/Tools/Ninja/ninja.exe `
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/qt6-mingw.cmake

C:\Qt\Tools\CMake_64\bin\cmake.exe --build build/manual-mingw-debug
```

The toolchain file reads `QT_ROOT` and `MINGW_ROOT` from the environment.

### Linux and macOS
The GitHub Actions workflow builds the same target on Linux and macOS with Qt 6. For local builds, install Qt 6 and then run:

```bash
cmake -S . -B build
cmake --build build
```

If Qt is not in a default system path, pass `-DCMAKE_PREFIX_PATH=/path/to/Qt`.

## CI and Releases
GitHub Actions builds desktop artifacts for Windows, Linux, and macOS. Tagged releases upload packaged archives for each platform.

## CLion
Recommended Windows setup:
- Toolchain uses `gcc.exe`, `g++.exe`, and `gdb.exe` from `C:\Qt\Tools\mingw1310_64\bin`
- CMake uses `C:\Qt\Tools\CMake_64\bin\cmake.exe`
- Build tool uses `C:\Qt\Tools\Ninja\ninja.exe`
- Environment provides `QT_ROOT=C:\Qt\6.10.2\mingw_64`
- Environment provides `MINGW_ROOT=C:\Qt\Tools\mingw1310_64`
- Select `windows-mingw-debug` or `windows-mingw-release` from CMake presets
