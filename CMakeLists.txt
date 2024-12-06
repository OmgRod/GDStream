cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(GDStream VERSION 1.0.0)

# Recursively include all the source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create a shared library from the source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Include the CPM package manager
include("cmake/CPM.cmake")

# Add and link IXWebSocket
CPMAddPackage("gh:cocos2d/cocos2d-x#v4")
target_link_libraries(${PROJECT_NAME} ixwebsocket)
target_include_directories(${PROJECT_NAME} PRIVATE ${ixwebsocket_INCLUDE_DIRS})

# Ensure Geode SDK environment variable is defined
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Add Geode SDK subdirectory
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Setup Geode mod
setup_geode_mod(${PROJECT_NAME})
