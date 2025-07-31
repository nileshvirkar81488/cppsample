# C++ Sample Project - Build Instructions

This project contains sample C++ code with a comprehensive build system using make.

## Quick Start

```bash
# Build all available targets
make

# Clean build artifacts
make clean

# Show help and available targets
make help

# Run tests (note: malloc_violation intentionally crashes to demonstrate memory violations)
./build/main  # Run the FaultHandler simulation
```

## Available Targets

### Currently Buildable:
- **malloc_violation** - Demonstrates C++ memory management violations (intentionally crashes)
- **main** - FaultHandler simulation program with DTC management

### Requires Additional Setup:
- **datetimecontroller** - Requires Qt libraries and TimeZoneModel implementation

## Build System Features

### Build Modes
```bash
make              # Debug build (default)
make DEBUG=1      # Explicit debug build
make RELEASE=1    # Optimized release build
```

### Available Commands
```bash
make all          # Build all available executables (default)
make clean        # Remove build artifacts
make test         # Run available test executables
make install      # Install executables to /usr/local/bin
make help         # Show help message
make info         # Show compiler and build information
```

### Build Structure
```
build/
├── obj/          # Object files
│   ├── main.o
│   ├── FaultHandler.o
│   └── malloc_violation.o
├── main          # FaultHandler executable
└── malloc_violation  # Memory violation demo
```

## Project Structure

```
.
├── Makefile                    # Build system
├── README.md                   # This file
├── main.cpp                    # FaultHandler simulation
├── FaultHandler.cpp            # FaultHandler implementation
├── FaultHandler.hpp            # FaultHandler header
├── malloc_violation.cpp        # Memory violation demo
├── datetimecontroller.cpp      # Qt-based controller (needs Qt setup)
├── include/
│   └── datetimecontroller.h    # DateTime controller header
└── common/
    └── Declarations.hpp        # Common project declarations
```

## Dependencies

### Currently Required:
- C++17 compatible compiler (g++ recommended)
- Standard C++ libraries

### For Full Build (datetimecontroller):
- Qt5 Core and Widgets libraries
- TimeZoneModel implementation (user-defined)

## Compiler Settings

- **Standard**: C++17
- **Include Paths**: `include/`, `.`
- **Warnings**: `-Wall -Wextra`
- **Debug Flags**: `-g -DDEBUG`
- **Release Flags**: `-O2 -DNDEBUG`

## Adding New Files

To add new C++ files to the build:

1. Add the source file to `BUILDABLE_SRCS` in the Makefile
2. If the file has special dependencies, create custom rules
3. Update the help text and documentation

## Example Output

### FaultHandler Simulation:
```bash
$ ./build/main
FaultHandler initialized
Checked and created necessary folders
Stored DTC: DTC001 for module: RADAR
Stored DTC: DTC002 for module: CAMERA
Stored DTC: DTC003 for module: ETHERNET
Handling DTC event: DTC001 for module: RADAR
Radar error handler called for DTC: DTC001
Logged DTCs to file: dtc_log_RADAR.txt
Logged DTCs to file: dtc_log_CAMERA.txt
Loading DTCs from file...
FaultHandler simulation completed.
```

## Notes

- The `malloc_violation` program intentionally demonstrates memory violations and will crash
- Log files are created in the current directory for DTC logging
- The build system automatically creates necessary directories
- Qt-based files require additional setup before they can be compiled
