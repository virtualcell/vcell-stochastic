cmake_minimum_required(VERSION 3.15)
project(VCellStochastic VERSION 1.0.0 LANGUAGES CXX C)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Default build type for single-config generators
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
option(OPTION_TARGET_MESSAGING "Enable messaging support" OFF)
option(OPTION_BUILD_PYTHON_BINDINGS "Build Python bindings using pybind11" OFF)

# scikit-build-core (pip wheel / cibuildwheel) only ever builds this project
# to produce the Python extension module.
if(SKBUILD)
    set(OPTION_BUILD_PYTHON_BINDINGS ON CACHE BOOL "Build Python bindings using pybind11" FORCE)
endif()

# Platform-specific compatibility
if(MSVC)
    add_compile_definitions(
            HAVE_UNISTD_H=0
            NOMINMAX
            _CRT_SECURE_NO_WARNINGS
    )
elseif(APPLE)
    execute_process(COMMAND uname -m OUTPUT_VARIABLE PROCESSOR_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(PROCESSOR_ARCHITECTURE STREQUAL "arm64")
        add_compile_definitions(__arm64__)
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    else()
        add_compile_definitions(__x86_64__)
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif()
elseif(UNIX)
    add_compile_options(-m64)
    add_compile_options(-fpermissive)
endif()

# Packages
find_package(Threads REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS C CXX)

# Optional messaging dependency
if(OPTION_TARGET_MESSAGING)
    find_package(CURL REQUIRED)
endif()

# Optional Python binding dependencies
if(OPTION_BUILD_PYTHON_BINDINGS)
    if(SKBUILD)
        # A wheel's extension module only needs Development.Module; the full
        # Development component additionally requires a libpython to embed,
        # which the manylinux/cibuildwheel images do not ship.
        find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)
    else()
        find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
    endif()
    find_package(pybind11 CONFIG REQUIRED)
endif()

# Apache Arrow / Parquet setup
if(OPTION_USE_PARQUET)
    # First try to find Arrow/Parquet via CMAKE_PREFIX_PATH (e.g., from vcpkg)
    find_package(Arrow QUIET)
    find_package(Parquet QUIET)
    
    # If not found, check if ARROW_INSTALL_DIR is provided
    if(NOT Arrow_FOUND AND ARROW_INSTALL_DIR)
        message(STATUS "Using pre-built Apache Arrow from: ${ARROW_INSTALL_DIR}")
        set(CMAKE_PREFIX_PATH "${ARROW_INSTALL_DIR};${CMAKE_PREFIX_PATH}")
        find_package(Arrow REQUIRED)
        find_package(Parquet REQUIRED)
    elseif(NOT Arrow_FOUND)
        message(FATAL_ERROR "OPTION_USE_PARQUET requires either CMAKE_PREFIX_PATH to be set (e.g., vcpkg installed location) or ARROW_INSTALL_DIR to be set. Example: -DARROW_INSTALL_DIR='C:/arrow-install'")
    endif()
        
    message(STATUS "Multi-trial output format: Parquet")
else()
    message(STATUS "Multi-trial output format: HDF5")
endif()

# Dependencies (vcell-expressionparser and vcell-messaging are git submodules)
add_subdirectory(vcell-expressionparser)
add_subdirectory(vcommons)
add_subdirectory(vcell-messaging)
add_subdirectory(VCellStoch)

# Testing
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(Tests)
endif()

if(OPTION_BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()

