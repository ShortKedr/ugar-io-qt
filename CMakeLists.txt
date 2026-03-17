cmake_minimum_required(VERSION 3.21)

project(ugar_io_qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

if(DEFINED ENV{QT_ROOT} AND NOT "$ENV{QT_ROOT}" STREQUAL "")
    file(TO_CMAKE_PATH "$ENV{QT_ROOT}" QT_ROOT_PATH)
    list(PREPEND CMAKE_PREFIX_PATH "${QT_ROOT_PATH}")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui OpenGL)

set(UGAR_IO_QT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/food.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/gamewindow.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/line.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ugar.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ugarai.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ugarplayer.cpp"
)

if(WIN32)
    list(APPEND UGAR_IO_QT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/resources/ugar-io-qt.rc")
endif()

if(WIN32)
    add_executable(ugar-io-qt WIN32 ${UGAR_IO_QT_SOURCES})
elseif(APPLE)
    add_executable(ugar-io-qt MACOSX_BUNDLE ${UGAR_IO_QT_SOURCES})
else()
    add_executable(ugar-io-qt ${UGAR_IO_QT_SOURCES})
endif()

target_include_directories(ugar-io-qt PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(ugar-io-qt PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::OpenGL)

set_target_properties(ugar-io-qt PROPERTIES
    OUTPUT_NAME "ugar-io-qt"
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ugar-io-qt)
endif()
