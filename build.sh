#!/bin/bash

# FastAPI-C++ Build and Run Script
# This script provides easy commands to build and run the FastAPI-C++ test server

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to show help
show_help() {
    echo "FastAPI-C++ Build and Run Script"
    echo "================================="
    echo ""
    echo "Usage: $0 [COMMAND]"
    echo ""
    echo "Commands:"
    echo "  build       - Build the library and test server using Make"
    echo "  cmake       - Build using CMake"
    echo "  run         - Build and run the test server"
    echo "  clean       - Clean build artifacts"
    echo "  test        - Run quick API tests"
    echo "  install     - Install the library system-wide"
    echo "  help        - Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 build    # Build with Make"
    echo "  $0 cmake    # Build with CMake"
    echo "  $0 run      # Build and run test server"
    echo "  $0 test     # Test the running server"
}

# Function to check dependencies
check_dependencies() {
    print_status "Checking dependencies..."
    
    # Check for C++ compiler
    if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
        print_error "No C++ compiler found. Please install g++ or clang++"
        exit 1
    fi
    
    # Check for Make
    if ! command -v make &> /dev/null; then
        print_error "Make not found. Please install make"
        exit 1
    fi
    
    print_success "All dependencies found"
}

# Function to build with Make
build_make() {
    print_status "Building with Make..."
    check_dependencies
    
    if [ ! -f "Makefile" ]; then
        print_error "Makefile not found!"
        exit 1
    fi
    
    make clean
    make all
    
    if [ $? -eq 0 ]; then
        print_success "Build completed successfully!"
        print_status "Library: build/libfastapi-cpp.a"
        print_status "Test server: build/test_server"
    else
        print_error "Build failed!"
        exit 1
    fi
}

# Function to build with CMake
build_cmake() {
    print_status "Building with CMake..."
    check_dependencies
    
    if [ ! -f "CMakeLists.txt" ]; then
        print_error "CMakeLists.txt not found!"
        exit 1
    fi
    
    # Create build directory
    mkdir -p build_cmake
    cd build_cmake
    
    # Configure and build
    cmake ..
    make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
    
    if [ $? -eq 0 ]; then
        print_success "CMake build completed successfully!"
        print_status "Library: build_cmake/libfastapi-cpp.a"
        print_status "Test server: build_cmake/test_server"
    else
        print_error "CMake build failed!"
        exit 1
    fi
    
    cd ..
}

# Function to run the test server
run_server() {
    print_status "Building and running test server..."
    
    # Build first
    build_make
    
    print_status "Starting test server..."
    print_status "Server will be available at: http://127.0.0.1:8080"
    print_status "Demo page: http://127.0.0.1:8080/demo"
    print_status "Health check: http://127.0.0.1:8080/health"
    print_status "Press Ctrl+C to stop the server"
    echo ""
    
    # Run the server
    ./build/test_server
}

# Function to test the API
test_api() {
    print_status "Testing API endpoints..."
    
    # Check if server is running
    if ! curl -s http://127.0.0.1:8080/health > /dev/null 2>&1; then
        print_error "Server is not running. Please start it first with: $0 run"
        exit 1
    fi
    
    print_status "Testing health endpoint..."
    curl -s http://127.0.0.1:8080/health | jq . 2>/dev/null || curl -s http://127.0.0.1:8080/health
    
    print_status "Testing stats endpoint..."
    curl -s http://127.0.0.1:8080/stats | jq . 2>/dev/null || curl -s http://127.0.0.1:8080/stats
    
    print_status "Testing user creation..."
    curl -s -X POST http://127.0.0.1:8080/users \
        -H "Content-Type: application/json" \
        -d '{"name":"Test User","age":25,"email":"test@example.com"}' | jq . 2>/dev/null || \
    curl -s -X POST http://127.0.0.1:8080/users \
        -H "Content-Type: application/json" \
        -d '{"name":"Test User","age":25,"email":"test@example.com"}'
    
    print_success "API tests completed!"
}

# Function to clean build artifacts
clean_build() {
    print_status "Cleaning build artifacts..."
    
    if [ -f "Makefile" ]; then
        make clean
    fi
    
    rm -rf build_cmake
    
    print_success "Clean completed!"
}

# Function to install the library
install_library() {
    print_status "Installing FastAPI-C++ library..."
    
    if [ ! -f "Makefile" ]; then
        print_error "Makefile not found!"
        exit 1
    fi
    
    make install
    
    if [ $? -eq 0 ]; then
        print_success "Library installed successfully!"
        print_status "Headers: /usr/local/include/fastapi-cpp/"
        print_status "Library: /usr/local/lib/libfastapi-cpp.a"
    else
        print_error "Installation failed!"
        exit 1
    fi
}

# Main script logic
case "${1:-help}" in
    "build")
        build_make
        ;;
    "cmake")
        build_cmake
        ;;
    "run")
        run_server
        ;;
    "test")
        test_api
        ;;
    "clean")
        clean_build
        ;;
    "install")
        install_library
        ;;
    "help"|"-h"|"--help")
        show_help
        ;;
    *)
        print_error "Unknown command: $1"
        echo ""
        show_help
        exit 1
        ;;
esac
