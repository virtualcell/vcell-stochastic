# VCell Stochastic Solver - Standalone Project

This is a standalone version of the VCell Stochastic solver, extracted from the main vcell-solvers repository.

## Overview

The VCell Stochastic solver implements stochastic simulation algorithms (Gibson/Gillespie) for biochemical reaction networks.

## Project Structure

```
vcell-stochastic/
├── CMakeLists.txt          # Root build configuration
├── VCellStoch/             # Main solver library and executable
│   ├── include/            # Header files
│   ├── src/                # Source files
│   └── CMakeLists.txt      # Solver build configuration
├── ExpressionParser/       # Expression parsing library (dependency)
├── vcommons/               # Common utilities (dependency)
├── VCellMessaging/         # Messaging support (dependency)
└── cmake/                  # CMake modules
```

## Building

### Prerequisites

- CMake 3.13 or higher
- C++14 compatible compiler
- HDF5 library (with C++ bindings)
- libcurl (optional, for messaging support)

### Build Instructions
#### Configure the build

On Linux/macOS:
```bash
cmake -S . -B build
```

On Windows:
```bash
cmake -S . -B build -G "Visual Studio 17 2022"
```

# Build the project
```bash
cmake --build build --config Release
```

The build produces:
- **Static library**: `build/bin/libVCellStochLib.a`
- **Executable**: `build/bin/VCellStoch`

### Build Options

- `BUILD_SHARED_LIBS` - Build shared libraries instead of static (default: OFF)
- `OPTION_TARGET_MESSAGING` - Enable messaging support (default: OFF)

Example with messaging enabled:
```bash
cmake -S . -B build -DOPTION_TARGET_MESSAGING=ON
cmake --build build --config Release
```

## Usage

### Running the Standalone Executable

```bash
./build/bin/VCellStoch {gibson|gillespie} input_filename output_filename
```

Options:
- `gibson` - Use Gibson's algorithm (Next Reaction Method)
- `gillespie` - Use Gillespie's algorithm (Direct Method)
- `input_filename` - Path to the input simulation file
- `output_filename` - Path for the output results

With messaging support (if built with OPTION_TARGET_MESSAGING):
```bash
./build/bin/VCellStoch {gibson|gillespie} input_filename output_filename [-tid 0]
```

### Using the Static Library

Link against `libVCellStochLib.a` and include the headers from `VCellStoch/include/`.

Key classes:
- `Gibson` - Main Gibson algorithm implementation
- `StochModel` - Stochastic model representation
- `Jump` - Reaction jump representation
- `StochVar` - Stochastic variable representation

To remove build artifacts:
```bash
cmake --build build --target clean
```

To completely remove the build directory:
```bash
rm -rf build
```

To install the built artifacts:

```bash
cmake --install build --prefix /path/to/install
```

This will install:
- Library to `<prefix>/lib/libVCellStochLib.a`
- Executable to `<prefix>/bin/VCellStoch`
- Headers to `<prefix>/include/VCellStoch/`

## Platform Support

- Linux (tested on Ubuntu/Debian)
- macOS (Intel and Apple Silicon)
- Windows (with appropriate toolchain)

## License

See the main VCell project for licensing information.
