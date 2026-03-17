if(NOT DEFINED ENV{QT_ROOT} OR "$ENV{QT_ROOT}" STREQUAL "")
    message(FATAL_ERROR "QT_ROOT environment variable is not set.")
endif()

if(NOT DEFINED ENV{MINGW_ROOT} OR "$ENV{MINGW_ROOT}" STREQUAL "")
    message(FATAL_ERROR "MINGW_ROOT environment variable is not set.")
endif()

file(TO_CMAKE_PATH "$ENV{QT_ROOT}" QT_ROOT_PATH)
file(TO_CMAKE_PATH "$ENV{MINGW_ROOT}" MINGW_ROOT_PATH)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER "${MINGW_ROOT_PATH}/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "${MINGW_ROOT_PATH}/bin/g++.exe")
set(CMAKE_RC_COMPILER "${MINGW_ROOT_PATH}/bin/windres.exe")
set(CMAKE_PREFIX_PATH "${QT_ROOT_PATH}" CACHE STRING "" FORCE)

if(EXISTS "${QT_ROOT_PATH}/bin")
    set(ENV{PATH} "${MINGW_ROOT_PATH}/bin;${QT_ROOT_PATH}/bin;$ENV{PATH}")
endif()
