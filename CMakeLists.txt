cmake_minimum_required(VERSION 3.21)

project(ugar_io_qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

if(UNIX AND NOT APPLE)
    include(GNUInstallDirs)
endif()

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
    add_executable(ugar-io-qt WIN32 ${UGAR_IO_QT_SOURCES})
elseif(APPLE)
    add_executable(ugar-io-qt MACOSX_BUNDLE ${UGAR_IO_QT_SOURCES})
else()
    add_executable(ugar-io-qt ${UGAR_IO_QT_SOURCES})
endif()

target_include_directories(ugar-io-qt PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(ugar-io-qt PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::OpenGL)

if(APPLE)
    set_target_properties(ugar-io-qt PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "Ugar.io Qt"
        MACOSX_BUNDLE_GUI_IDENTIFIER "io.shortkedr.ugarioqt"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0"
    )
endif()

if(APPLE)
    target_compile_definitions(ugar-io-qt PRIVATE GL_SILENCE_DEPRECATION)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ugar-io-qt)
endif()

if(UNIX AND NOT APPLE)
    install(TARGETS ugar-io-qt
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    qt_generate_deploy_app_script(
        TARGET ugar-io-qt
        FILENAME_VARIABLE ugar_io_qt_linux_deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )

    install(SCRIPT "${ugar_io_qt_linux_deploy_script}")
endif()
