# FastAPI-C++ Build System - Complete Setup

### 📁 Build System Files

1. **`Makefile`** - Traditional Make-based build system
2. **`CMakeLists.txt`** - Modern CMake build system  
3. **`build.sh`** - Cross-platform build script (Linux/macOS)
4. **`build.bat`** - Windows batch script
5. **`dev.sh`** - Development helper script
6. **`BUILD.md`** - Comprehensive build documentation

### 🚀 Example Applications

1. **`examples/test_server.cpp`** - Comprehensive test server demonstrating all features
2. **`examples/simple_example.cpp`** - Minimal example for quick start

### 📚 Documentation

- **`BUILD.md`** - Complete build system documentation
- Updated **`README.md`** with build instructions

## 🛠️ Quick Start Guide

### Option 1: Using Build Script (Recommended)
```bash
# Make executable (first time only)
chmod +x build.sh

# Build and run comprehensive test server
./build.sh run

# Build and run simple example
make run-simple
```

### Option 2: Using Make Directly
```bash
# Build everything
make all

# Run comprehensive test server
make run

# Run simple example
make run-simple

# Clean build artifacts
make clean
```

### Option 3: Using CMake
```bash
mkdir build_cmake && cd build_cmake
cmake ..
make -j$(nproc)
./test_server
```

## 🌐 Test Server Features

The comprehensive test server (`examples/test_server.cpp`) includes:

### **User Management**
- `GET /users` - List all users
- `POST /users` - Create user with validation
- `GET /users/{id}` - Get user by ID
- `PUT /users/{id}` - Update user
- `DELETE /users/{id}` - Delete user

### **Product Management**
- `GET /products` - List all products
- `POST /products` - Create product with validation
- `GET /products/{id}` - Get product by ID
- `PUT /products/{id}` - Update product
- `DELETE /products/{id}` - Delete product

### **Order Management**
- `GET /orders` - List all orders
- `POST /orders` - Create order with validation
- `GET /orders/{id}` - Get order by ID

### **System Endpoints**
- `GET /` - Server information
- `GET /health` - Health check
- `GET /stats` - Server statistics
- `GET /demo` - Interactive HTML demo page

## 🧪 Testing the API

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
```

### Using the Test Script
```bash
# Run automated tests
./build.sh test
```

### Interactive Demo
Visit http://127.0.0.1:8080/demo for an interactive web interface

## 🔧 Development Workflow

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

# Run with gdb
gdb ./build/test_server
```

## 📋 Available Commands

### Make Targets
- `make all` - Build library and all examples
- `make test-server` - Build comprehensive test server
- `make simple-example` - Build simple example
- `make run` - Build and run test server
- `make run-simple` - Build and run simple example
- `make clean` - Clean build artifacts
- `make debug` - Build with debug symbols
- `make release` - Build with optimizations
- `make install` - Install system-wide

### Build Script Commands
- `./build.sh build` - Build using Make
- `./build.sh cmake` - Build using CMake
- `./build.sh run` - Build and run test server
- `./build.sh test` - Test the running server
- `./build.sh clean` - Clean build artifacts
- `./build.sh install` - Install system-wide

### Development Script Commands
- `./dev.sh run` - Quick build and run
- `./dev.sh test` - Run quick tests with sample data
- `./dev.sh watch` - Watch mode (rebuild on file changes)
- `./dev.sh debug` - Build debug version
- `./dev.sh perf` - Run performance test

## 🎯 Next Steps

1. **Start the server**: `./build.sh run`
2. **Visit the demo**: http://127.0.0.1:8080/demo
3. **Test the API**: Use curl or the interactive demo
4. **Explore the code**: Check `examples/` for usage patterns
5. **Build your own app**: Use the library in your projects

## 🔍 What's Working

✅ **Build System**: Make, CMake, and build scripts all working  
✅ **Library**: Static library `libfastapi-cpp.a` built successfully  
✅ **Examples**: Both simple and comprehensive examples compile and run  
✅ **Documentation**: Complete build documentation provided  
✅ **Cross-platform**: Works on Linux, macOS, and Windows  
✅ **Development Tools**: Watch mode, debug builds, performance testing  


