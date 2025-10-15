# FastAPI-CPP 🚀
<img width="250" height="250" alt="fastapi-cpp" src="https://github.com/user-attachments/assets/6ba2212a-84ee-4df5-8d1e-c66b6d494cb2" />

A modern, FastAPI-inspired web framework for **C++17** and above, built on top of [cpp-httplib](https://github.com/yhirose/cpp-httplib) and [nlohmann/json](https://github.com/nlohmann/json). 

Write clean, type-safe, and declarative APIs in C++ with path params, request body models, and automatic JSON serialization.

---

## ✨ Features

- FastAPI-style routing
- Path parameters
- Request body models with validation
- Automatic JSON serialization
- Simple response handling
- Centralized server runner
- Extensible validation layer
- Supports all HTTP methods: GET, POST, PUT, PATCH, DELETE, OPTIONS, HEAD

---

## 🛠️ Build System Overview

FastAPI-C++ includes a comprehensive build system supporting multiple build and run methods.  
You can use **Make**, **CMake**, or provided **build scripts** to compile and run the examples.

### 📁 Build System Files

1. **`Makefile`** — Traditional Make-based build system  
2. **`CMakeLists.txt`** — Modern CMake build system  
3. **`build.sh` / `build.bat`** — Cross-platform build scripts  
4. **`dev.sh`** — Development helper script  
5. **`BUILD.md`** — Comprehensive build documentation  

### 🚀 Example Applications
- `examples/test_server.cpp` — Comprehensive test server demonstrating all features  
- `examples/simple_example.cpp` — Minimal example for quick start  

---

## ⚡ Quick Build & Run

### Option 1: Using Build Script (Recommended)
```bash
chmod +x build.sh
./build.sh run
```

### Option 2: Using Make Directly
```bash
make all
make run
make run-simple
make clean
```

### Option 3: Using CMake
```bash
mkdir build_cmake && cd build_cmake
cmake ..
make -j$(nproc)
./test_server
```

---

## 🌐 Example Endpoints

The test server provides ready-to-use endpoints:

### User Management
- `GET /users`
- `POST /users`
- `GET /users/{id}`
- `PUT /users/{id}`
- `DELETE /users/{id}`

### Product Management
- `GET /products`
- `POST /products`
- `GET /products/{id}`
- `PUT /products/{id}`
- `DELETE /products/{id}`

### System Endpoints
- `GET /` — Server info  
- `GET /health` — Health check  
- `GET /stats` — Server statistics  
- `GET /demo` — Interactive demo page  

---

## 🧪 Testing the API

### Using curl
```bash
curl http://127.0.0.1:8080/health
curl -X POST http://127.0.0.1:8080/users -H "Content-Type: application/json" -d '{"name":"John Doe","age":30}'
curl http://127.0.0.1:8080/users
```

### Using Test Script
```bash
./build.sh test
```

### Interactive Demo
Visit [http://127.0.0.1:8080/demo](http://127.0.0.1:8080/demo)

---

## 📋 Make Targets

- `make all` — Build library and examples  
- `make run` — Run comprehensive test server  
- `make run-simple` — Run minimal example  
- `make clean` — Clean build artifacts  
- `make debug` — Build with debug symbols  
- `make release` — Build optimized version  

---

## 🧰 Development Commands

```bash
./dev.sh run       # Quick build and run
./dev.sh test      # Run quick tests
./dev.sh watch     # Auto rebuild on file change
./dev.sh debug     # Debug build
./dev.sh perf      # Run performance test
```

---

## 💡 Development Example (Quick Start)

```cpp
#include "fastapi_cpp.h"

Router app;

Response read_item(int item_id) {
    return Response(json{{"item_id", item_id}});
}

Response create_user(std::string name, int age) {
    return Response(json{{"name", name}, {"age", age}});
}

int main() {
    APP_GET("/items/{item_id}", read_item, Path<int>);
    APP_POST("/users", create_user, Query<std::string>, Query<int>);

    FastApiCpp::run(app, "127.0.0.1", 8080);
}
```

---

## 🙏 Acknowledgements

This project builds on:

- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [nlohmann/json](https://github.com/nlohmann/json)
