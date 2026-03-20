cmake_minimum_required(VERSION 3.13)
project(VCellStochastic VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable CXX and C
enable_language(CXX)
enable_language(C)

# Architecture flags
if (APPLE)
    execute_process(COMMAND uname -m OUTPUT_VARIABLE PROCESSOR_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (PROCESSOR_ARCHITECTURE STREQUAL "arm64")
        add_definitions(-D__arm64__)
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    else()
        add_definitions(-D__x86_64__)
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif()
elseif (UNIX)
    # Default to 64-bit on Linux/Unix
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
endif()

# Compile flags
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()

if (MSVC)
    add_definitions(-DHAVE_UNISTD_H=0)
endif()

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(OPTION_TARGET_MESSAGING "Enable messaging support" OFF)

# Find required packages
find_package(HDF5 COMPONENTS CXX REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# Find threading library
find_package(Threads REQUIRED)

# Find CURL if messaging is enabled
if(OPTION_TARGET_MESSAGING)
    find_package(CURL REQUIRED)
endif()

# Add subdirectories for dependencies
add_subdirectory(ExpressionParser)
add_subdirectory(vcommons)
add_subdirectory(VCellMessaging)

# Add the main VCellStoch library
add_subdirectory(VCellStoch)
