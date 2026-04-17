# VCell Stochastic Solver - Standalone Project

This is a standalone version of the VCell Stochastic solver, extracted from the main vcell-solvers repository.

## Overview

The VCell Stochastic solver implements stochastic simulation algorithms (Gibson/Gillespie) for biochemical reaction networks.

## Project Structure

The project is organized as follows:
- CMakeLists.txt: Root build configuration
- VCellStoch: Main solver library and executable with include and src subdirectories
- ExpressionParser: Expression parsing library dependency
- vcommons: Common utilities dependency
- VCellMessaging: Messaging support dependency
- Tests: Unit tests
- cmake: CMake modules

## Building

### Prerequisites

- CMake 3.13 or higher
- C++14 compatible compiler
- HDF5 library with C and C++ components
- libcurl (optional, for messaging support)

### Build Instructions

#### Linux/macOS

    cmake -S . -B build
    cmake --build build --config Release

#### Windows

    cmake --preset windows-msvc-hdf5
    cmake --build --preset windows-msvc-hdf5

If you are not using presets, configure manually and provide the HDF5 installation path:

    cmake -S . -B build -DHDF5_ROOT="C:\Program Files\HDF_Group\HDF5\2.1.0"
    cmake --build build --config Release

If CMake still cannot find HDF5 on Windows, set one or both of these variables before configuring:

- `HDF5_ROOT` — HDF5 installation prefix
- `HDF5_DIR` — directory containing HDF5 CMake package files, if available

The build produces:
- Static library: build/bin/libVCellStochLib.a (Linux/macOS) or build/bin/VCellStochLib.lib (Windows)
- Executable: build/bin/VCellStoch (Linux/macOS) or build\bin\VCellStoch.exe (Windows)

### Build Options

- BUILD_SHARED_LIBS: Build shared libraries instead of static (default: OFF)
- BUILD_TESTING: Enable smoke tests (default: ON)

## Testing

Tests are located in the Tests directory and use a custom test framework (no external test library required).

### Running Tests

#### Linux/macOS

Configure with testing enabled, then run:

    cmake -S . -B build -DBUILD_TESTING=ON
    cmake --build build
    ctest --test-dir build --verbose

#### Windows (with presets)

    cmake --preset windows-msvc-hdf5 -DBUILD_TESTING=ON
    cmake --build --preset windows-msvc-hdf5
    ctest --test-dir build/windows-msvc-hdf5 --verbose

#### Windows (without presets)

    cmake -S . -B build -DBUILD_TESTING=ON -DHDF5_ROOT="C:\Program Files\HDF_Group\HDF5\2.1.0"
    cmake --build build --config Release
    ctest --test-dir build --verbose

Alternatively, run the test executable directly:

    .\build\windows-msvc-hdf5\bin\TestVCellStoch.exe

## Usage

### Running the Standalone Executable

    ./build/bin/VCellStoch {gibson|gillespie} input_filename output_filename

Options:
- gibson: Use Gibson's algorithm (Next Reaction Method)
- gillespie: Use Gillespie's algorithm (Direct Method)
- input_filename: Path to the input simulation file
- output_filename: Path for the output results

With messaging support (if built with OPTION_TARGET_MESSAGING):

    ./build/bin/VCellStoch {gibson|gillespie} input_filename output_filename [-tid 0]

### Using the Static Library

Link against libVCellStochLib.a (Linux/macOS) or VCellStochLib.lib (Windows) and include the headers from VCellStoch/include/.

Key classes:
- Gibson: Main Gibson algorithm implementation
- StochModel: Stochastic model representation
- Jump: Reaction jump representation
- StochVar: Stochastic variable representation

## Cleanup

To remove build artifacts:

    cmake --build build --target clean

To completely remove the build directory:

    rm -rf build

## Installation

To install the built artifacts:

    cmake --install build --prefix /path/to/install

This will install:
- Library to <prefix>/lib/libVCellStochLib.a (Linux/macOS) or <prefix>/lib/VCellStochLib.lib (Windows)
- Executable to <prefix>/bin/VCellStoch
- Headers to <prefix>/include/VCellStoch/

## Platform Support

- Linux (tested on Ubuntu/Debian)
- macOS (Intel and Apple Silicon)
- Windows (with MSVC via presets)

## License

See the main VCell project for licensing information.
