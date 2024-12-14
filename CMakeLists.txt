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

# start of copy of creator rotation code

set(USE_ZLIB OFF)
if (NOT APPLE)
    set(USE_MBED_TLS ON)
endif()

set(USE_OPEN_SSL OFF)
set(USE_TLS ON)
SET(CMAKE_C_SIMULATE_ID "Clang")
set(ENABLE_PROGRAMS OFF)
set(ENABLE_TESTING OFF)
set(MBEDTLS_AS_SUBPROJECT OFF)
set(DISABLE_PACKAGE_CONFIG_AND_INSTALL OFF)
set(MBEDTLS_FATAL_WARNINGS OFF)

CPMAddPackage("gh:TechStudent10/mbedtls#fc79213")

set(MBEDTLS_INCLUDE_DIRS "${mbedtls_SOURCE_DIR}/include")
set(MBEDTLS_LIBRARY "mbedtls")
set(MBEDX509_LIBRARY "mbedx509")
set(MBEDCRYPTO_LIBRARY "mbedcrypto")

CPMAddPackage("gh:machinezone/IXWebSocket#dc8807e")
install(TARGETS mbedtls mbedx509 mbedcrypto EXPORT mbedtls-targets)

if (WIN32)
    if (CR_DEBUG)
        target_compile_definitions(mbedtls PRIVATE _HAS_ITERATOR_DEBUGGING=0)
        target_compile_definitions(ixwebsocket PRIVATE _HAS_ITERATOR_DEBUGGING=0)
    endif()
endif()

# end of copy of creator rotation code

CPMAddPackage("gh:FFmpeg/FFmpeg#master")
target_link_libraries(${PROJECT_NAME} ffmpeg)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})