#!/bin/bash

# FastAPI-C++ Development Script
# Quick development commands for testing and debugging

set -e

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_status() {
    echo -e "${BLUE}[DEV]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Quick build and run
dev_run() {
    print_status "Quick build and run..."
    make clean && make all && ./build/test_server
}

# Quick test with sample data
dev_test() {
    print_status "Running quick tests..."
    
    # Start server in background
    ./build/test_server &
    SERVER_PID=$!
    
    # Wait for server to start
    sleep 2
    
    print_status "Testing basic endpoints..."
    
    # Test health
    curl -s http://127.0.0.1:8080/health | jq . 2>/dev/null || echo "Health check failed"
    
    # Create test data
    print_status "Creating test data..."
    
    # Create users
    curl -s -X POST http://127.0.0.1:8080/users \
        -H "Content-Type: application/json" \
        -d '{"name":"Alice","age":30,"email":"alice@example.com"}' | jq . 2>/dev/null || echo "User creation failed"
    
    curl -s -X POST http://127.0.0.1:8080/users \
        -H "Content-Type: application/json" \
        -d '{"name":"Bob","age":25,"email":"bob@example.com"}' | jq . 2>/dev/null || echo "User creation failed"
    
    # Create products
    curl -s -X POST http://127.0.0.1:8080/products \
        -H "Content-Type: application/json" \
        -d '{"name":"Laptop","price":999.99,"description":"High-performance laptop","stock":10}' | jq . 2>/dev/null || echo "Product creation failed"
    
    curl -s -X POST http://127.0.0.1:8080/products \
        -H "Content-Type: application/json" \
        -d '{"name":"Mouse","price":29.99,"description":"Wireless mouse","stock":50}' | jq . 2>/dev/null || echo "Product creation failed"
    
    # Create order
    curl -s -X POST http://127.0.0.1:8080/orders \
        -H "Content-Type: application/json" \
        -d '{"user_id":1,"product_ids":[1,2],"total_amount":1029.98}' | jq . 2>/dev/null || echo "Order creation failed"
    
    print_status "Current data:"
    curl -s http://127.0.0.1:8080/stats | jq . 2>/dev/null || curl -s http://127.0.0.1:8080/stats
    
    # Stop server
    kill $SERVER_PID 2>/dev/null || true
    
    print_success "Quick tests completed!"
}

# Watch mode - rebuild and restart on file changes
dev_watch() {
    print_status "Starting watch mode..."
    print_warning "This requires 'fswatch' to be installed"
    
    if ! command -v fswatch &> /dev/null; then
        print_warning "fswatch not found. Install with: brew install fswatch (macOS) or apt-get install fswatch (Linux)"
        exit 1
    fi
    
    print_status "Watching for changes in src/ and include/ directories..."
    
    fswatch -o src/ include/ | while read; do
        print_status "Files changed, rebuilding..."
        make clean && make all
        if [ $? -eq 0 ]; then
            print_success "Rebuild successful!"
        else
            print_warning "Rebuild failed!"
        fi
    done
}

# Debug build
dev_debug() {
    print_status "Building debug version..."
    make clean
    make debug
    print_success "Debug build completed!"
}

# Performance test
dev_perf() {
    print_status "Running performance test..."
    
    # Start server
    ./build/test_server &
    SERVER_PID=$!
    sleep 2
    
    print_status "Running 100 concurrent requests..."
    
    # Create test data first
    curl -s -X POST http://127.0.0.1:8080/users \
        -H "Content-Type: application/json" \
        -d '{"name":"PerfTest","age":25,"email":"perf@test.com"}' > /dev/null
    
    # Run performance test
    start_time=$(date +%s.%N)
    
    for i in {1..100}; do
        curl -s http://127.0.0.1:8080/users/1 > /dev/null &
    done
    
    wait
    end_time=$(date +%s.%N)
    
    duration=$(echo "$end_time - $start_time" | bc)
    rps=$(echo "100 / $duration" | bc)
    
    print_success "Performance test completed!"
    print_status "Duration: ${duration}s"
    print_status "Requests per second: ${rps}"
    
    # Stop server
    kill $SERVER_PID 2>/dev/null || true
}

# Show help
show_help() {
    echo "FastAPI-C++ Development Script"
    echo "=============================="
    echo ""
    echo "Usage: $0 [COMMAND]"
    echo ""
    echo "Commands:"
    echo "  run         - Quick build and run"
    echo "  test        - Run quick tests with sample data"
    echo "  watch       - Watch mode (rebuild on file changes)"
    echo "  debug       - Build debug version"
    echo "  perf        - Run performance test"
    echo "  help        - Show this help"
    echo ""
    echo "Examples:"
    echo "  $0 run      # Quick build and run"
    echo "  $0 test     # Test with sample data"
    echo "  $0 watch    # Watch for changes"
}

# Main logic
case "${1:-help}" in
    "run")
        dev_run
        ;;
    "test")
        dev_test
        ;;
    "watch")
        dev_watch
        ;;
    "debug")
        dev_debug
        ;;
    "perf")
        dev_perf
        ;;
    "help"|"-h"|"--help")
        show_help
        ;;
    *)
        echo "[ERROR] Unknown command: $1"
        echo ""
        show_help
        exit 1
        ;;
esac
