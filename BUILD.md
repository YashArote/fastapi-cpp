# FastAPI-C++ Build System

This document explains how to build and run the FastAPI-C++ library and examples.

## Quick Start

### Using the Build Script (Recommended)

The easiest way to build and run FastAPI-C++ is using the provided build script:

```bash
# Make the script executable (first time only)
chmod +x build.sh

# Build and run the comprehensive test server
./build.sh run

# Or build and run the simple example
make run-simple
```

### Using Make Directly

```bash
# Build everything (library + examples)
make all

# Build and run the comprehensive test server
make run

# Build and run the simple example
make run-simple

# Clean build artifacts
make clean
```

### Using CMake

```bash
# Create build directory
mkdir build_cmake && cd build_cmake

# Configure and build
cmake ..
make -j$(nproc)

# Run the test server
./test_server
```

## Available Build Targets

### Make Targets

| Target | Description |
|--------|-------------|
| `all` | Build library and all examples (default) |
| `test-server` | Build only the comprehensive test server |
| `simple-example` | Build only the simple example |
| `run` | Build and run the test server |
| `run-simple` | Build and run the simple example |
| `clean` | Remove build artifacts |
| `debug` | Build with debug symbols |
| `release` | Build with optimizations |
| `install` | Install headers and library system-wide |
| `help` | Show help message |

### Build Script Commands

| Command | Description |
|---------|-------------|
| `./build.sh build` | Build using Make |
| `./build.sh cmake` | Build using CMake |
| `./build.sh run` | Build and run test server |
| `./build.sh test` | Test the running server |
| `./build.sh clean` | Clean build artifacts |
| `./build.sh install` | Install system-wide |

### Development Script Commands

| Command | Description |
|---------|-------------|
| `./dev.sh run` | Quick build and run |
| `./dev.sh test` | Run quick tests with sample data |
| `./dev.sh watch` | Watch mode (rebuild on file changes) |
| `./dev.sh debug` | Build debug version |
| `./dev.sh perf` | Run performance test |

## Examples

### 1. Comprehensive Test Server

The comprehensive test server (`examples/test_server.cpp`) demonstrates all FastAPI-C++ features:

- **User Management**: CRUD operations for users
- **Product Management**: CRUD operations for products  
- **Order Management**: Create and retrieve orders
- **Data Validation**: Model validation with custom rules
- **HTML Responses**: Serves an interactive demo page
- **Error Handling**: Proper HTTP status codes and error messages

**Endpoints:**
- `GET /` - Server information
- `GET /health` - Health check
- `GET /stats` - Server statistics
- `GET /demo` - Interactive HTML demo page
- `GET /users` - List all users
- `POST /users` - Create user
- `GET /users/{id}` - Get user by ID
- `PUT /users/{id}` - Update user
- `DELETE /users/{id}` - Delete user
- Similar endpoints for products and orders

**Run it:**
```bash
make run
# or
./build.sh run
```

Then visit: http://127.0.0.1:8080/demo

### 2. Simple Example

The simple example (`examples/simple_example.cpp`) shows basic FastAPI-C++ usage:

- **Basic Routes**: GET and POST endpoints
- **Path Parameters**: Extract parameters from URL paths
- **Request Body Models**: Parse and validate JSON request bodies
- **HTML Responses**: Serve HTML content

**Endpoints:**
- `GET /` - Hello message
- `GET /users/{id}` - Get user by ID
- `POST /users` - Create a new user
- `GET /demo` - HTML demo page

**Run it:**
```bash
make run-simple
```

## Testing the API

### Using curl

```bash
# Health check
curl http://127.0.0.1:8080/health

# Create a user
curl -X POST http://127.0.0.1:8080/users \
  -H "Content-Type: application/json" \
  -d '{"name":"John Doe","age":30,"email":"john@example.com"}'

# Get all users
curl http://127.0.0.1:8080/users

# Get user by ID
curl http://127.0.0.1:8080/users/1
```

### Using the Test Script

```bash
# Run automated tests
./build.sh test
# or
./dev.sh test
```

## Development Workflow

### Quick Development

```bash
# Quick build and run
./dev.sh run

# Run tests with sample data
./dev.sh test

# Watch for changes and rebuild
./dev.sh watch
```

### Debugging

```bash
# Build with debug symbols
make debug
# or
./dev.sh debug

# Run with gdb
gdb ./build/test_server
```

### Performance Testing

```bash
# Run performance tests
./dev.sh perf
```

## System Requirements

### Dependencies

- **C++ Compiler**: g++ 7+ or clang++ 7+
- **Make**: GNU Make or compatible
- **CMake**: 3.16+ (optional, for CMake builds)
- **curl**: For testing (optional)
- **jq**: For JSON formatting in tests (optional)

### Platform Support

- **Linux**: Full support
- **macOS**: Full support  
- **Windows**: Supported via MinGW/MSYS2 or WSL

## Installation

### System-wide Installation

```bash
# Install headers and library
make install
# or
./build.sh install
```

This installs:
- Headers: `/usr/local/include/fastapi-cpp/`
- Library: `/usr/local/lib/libfastapi-cpp.a`

### Using in Your Project

After installation, you can use FastAPI-C++ in your projects:

```cpp
#include <fastapi-cpp/server.hpp>
#include <fastapi-cpp/macros.hpp>

// Your code here
```

Compile with:
```bash
g++ -std=c++17 your_app.cpp -lfastapi-cpp -pthread -o your_app
```

## Troubleshooting

### Common Issues

1. **Compilation Errors**: Ensure you're using C++17 or later
2. **Missing Dependencies**: Install required packages for your platform
3. **Port Already in Use**: Change the port in the example code
4. **Permission Errors**: Use `sudo` for system-wide installation

### Getting Help

- Check the main README.md for usage examples
- Look at the example files in `examples/`
- Use `make help` or `./build.sh help` for build options

## Build Configuration

### Compiler Flags

- **Debug**: `-g -DDEBUG`
- **Release**: `-O3 -DNDEBUG`
- **Default**: `-O2`

### Customization

You can modify the build configuration by editing:
- `Makefile` - For Make-based builds
- `CMakeLists.txt` - For CMake builds
- `build.sh` - For build script behavior
