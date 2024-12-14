cmake_minimum_required(VERSION 3.21)

# Project Configuration
project(GDStream VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

# Gather Source Files
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Include CPM for Dependency Management
include("cmake/CPM.cmake")

# Check Geode SDK Environment Variable
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode SDK at $ENV{GEODE_SDK}")
endif()


# Dependency: mbedTLS (for secure communication)
set(USE_ZLIB OFF)
set(USE_OPEN_SSL OFF)
set(USE_TLS ON)
set(ENABLE_PROGRAMS OFF)
set(ENABLE_TESTING OFF)
set(MBEDTLS_AS_SUBPROJECT OFF)
set(MBEDTLS_FATAL_WARNINGS OFF)

CPMAddPackage("gh:Mbed-TLS/mbedtls#development")
target_include_directories(${PROJECT_NAME} PRIVATE ${mbedtls_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE mbedtls mbedx509 mbedcrypto)

# Dependency: IXWebSocket (for WebSocket communication)
CPMAddPackage("gh:machinezone/IXWebSocket#dc8807e")
target_link_libraries(${PROJECT_NAME} PRIVATE ixwebsocket)

# Dependency: FFmpeg (for multimedia support)
CPMAddPackage(
    NAME FFmpeg
    GITHUB_REPOSITORY BtbN/FFmpeg-Builds
    VERSION 6.0
    DOWNLOAD_ONLY ON
    )
    set(FFMPEG_INCLUDE_DIR ${FFmpeg_SOURCE_DIR}/include)
    set(FFMPEG_LIBRARY_DIR ${FFmpeg_SOURCE_DIR}/lib)
    target_include_directories(${PROJECT_NAME} PRIVATE ${FFMPEG_INCLUDE_DIR})
    target_link_directories(${PROJECT_NAME} PRIVATE ${FFMPEG_LIBRARY_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE avformat avcodec avutil)
    
    # Ensure Visibility and Optimization
    set_target_properties(${PROJECT_NAME} PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    )
    
    # Debug Information
    message(STATUS "FFmpeg Include Directory: ${FFMPEG_INCLUDE_DIR}")
    message(STATUS "FFmpeg Library Directory: ${FFMPEG_LIBRARY_DIR}")
    message(STATUS "Geode SDK: $ENV{GEODE_SDK}")
    
    # Add Geode SDK
    add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
    setup_geode_mod(${PROJECT_NAME})