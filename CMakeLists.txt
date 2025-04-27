cmake_minimum_required(VERSION 3.5)

project(BBOverFloaw VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network WebSockets Gui Multimedia Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network WebSockets Gui Multimedia Test)

find_program(CCACHE_PROGRAM ccache)


if(CCACHE_PROGRAM)
    message(STATUS "ccache is available: ${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
else()
    message(WARNING "ccache is not installed or not found in PATH.")
endif()

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE UIS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

# set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Telegram/lib/cmake/TgBot" ${CMAKE_PREFIX_PATH})

# find_package(TgBot)


# include(FetchContent)
# FetchContent_Declare(TgBot
#     SYSTEM
#     GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp
#     # GIT_TAG a609330e4c6374f741d3b369269f7848255e1954 # v0.14.1
#     GIT_TAG 1b10d2fb99252027ae65fe782308a27a01adbc19 # v1.9
#     GIT_SHALLOW TRUE
#     # SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/tgbot-cpp-1.9
# )
# FetchContent_MakeAvailable(TgBot)


include_directories("${CMAKE_SOURCE_DIR}")

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/icon/appico.rc")


set(PROJECT_SOURCES
        ${HEADERS}
        ${SOURCES}
        ${UIS}
        ${app_icon_resource_windows}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BBOverFloaw
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        chart/VolumePercentGraph.h chart/VolumePercentGraph.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BBOverFloaw APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BBOverFloaw SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BBOverFloaw
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BBOverFloaw PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::WebSockets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::Test
# TgBot
)

set_target_properties(BBOverFloaw PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS BBOverFloaw
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BBOverFloaw)
endif()
