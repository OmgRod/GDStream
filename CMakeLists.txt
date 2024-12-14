cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(GDStream VERSION 1.0.0)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

include("cmake/CPM.cmake")

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

set(USE_ZLIB OFF)
if (NOT APPLE)
    set(USE_MBED_TLS ON)
endif()

CPMAddPackage("gh:machinezone/IXWebSocket#master")
target_link_libraries(${PROJECT_NAME} ixwebsocket)

CPMAddPackage("gh:FFmpeg/FFmpeg#master")
target_link_libraries(${PROJECT_NAME} ffmpeg)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})