# Ugar.io Qt
[![Build Desktop Binaries](https://github.com/ShortKedr/ugar-io-qt/actions/workflows/build-desktop.yml/badge.svg)](https://github.com/ShortKedr/ugar-io-qt/actions/workflows/build-desktop.yml)

Simplest single-player copy of Agar.io game, made with C++ and Qt.

This project has another implementation with OpenGL: [watch here](https://github.com/ShortKedr/ugar-io-opengl).

## Project Layout
- `src/` contains implementation files
- `include/ugar_io_qt/` contains project headers
- `resources/` contains Windows resource files and deployment metadata
- `cmake/toolchains/` contains helper toolchain files
- `CMakeLists.txt` is the primary build entrypoint
- `CMakePresets.json` contains ready-to-use Windows MinGW presets

## Requirements
1. CMake 3.21 or newer
1. A C++20-capable compiler toolchain
1. Qt 6 with `Core`, `Gui`, and `OpenGL`
1. On Windows MinGW builds: Qt `MinGW 64-bit`, MinGW, CMake, and Ninja from the Qt installer

## Build with CMake
### Windows with Qt6 + MinGW
This is the primary local development path for the repository.

Set these environment variables before running CMake or opening CLion:

```powershell
$env:QT_ROOT="C:\Qt\6.10.2\mingw_64"
$env:MINGW_ROOT="C:\Qt\Tools\mingw1310_64"
```

Configure and build with presets:

```powershell
C:\Qt\Tools\CMake_64\bin\cmake.exe --preset windows-mingw-debug
C:\Qt\Tools\CMake_64\bin\cmake.exe --build --preset build-windows-mingw-debug
```

Release build:

```powershell
C:\Qt\Tools\CMake_64\bin\cmake.exe --preset windows-mingw-release
C:\Qt\Tools\CMake_64\bin\cmake.exe --build --preset build-windows-mingw-release
```

Produced binaries:
- `build/windows-mingw-debug/ugar-io-qt.exe`
- `build/windows-mingw-release/ugar-io-qt.exe`

### Windows with manual CMake arguments
If you do not want to use presets, pass the same Qt and MinGW paths directly:

```powershell
C:\Qt\Tools\CMake_64\bin\cmake.exe -S . -B build/manual-mingw-debug -G Ninja `
  -DCMAKE_BUILD_TYPE=Debug `
  -DCMAKE_MAKE_PROGRAM=C:/Qt/Tools/Ninja/ninja.exe `
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/qt6-mingw.cmake

C:\Qt\Tools\CMake_64\bin\cmake.exe --build build/manual-mingw-debug
```

The toolchain file reads `QT_ROOT` and `MINGW_ROOT` from the environment.

### Linux and macOS
On non-Windows platforms, install Qt 6 development packages and use regular CMake:

```bash
cmake -S . -B build
cmake --build build
```

If Qt is not in a default system path, set `QT_ROOT` or pass `-DCMAKE_PREFIX_PATH=/path/to/Qt`.

## CLion
Recommended setup:
- Toolchain uses `gcc.exe`, `g++.exe`, and `gdb.exe` from `C:\Qt\Tools\mingw1310_64\bin`
- CMake uses `C:\Qt\Tools\CMake_64\bin\cmake.exe`
- Build tool uses `C:\Qt\Tools\Ninja\ninja.exe`
- Environment provides:
  - `QT_ROOT=C:\Qt\6.10.2\mingw_64`
  - `MINGW_ROOT=C:\Qt\Tools\mingw1310_64`
- Select `windows-mingw-debug` or `windows-mingw-release` from CMake presets

An example env file is available at `.env.clion`.
