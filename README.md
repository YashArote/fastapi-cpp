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
# 🛠️ Installation & Integration Guide (FastAPI-CPP)

## 1. Clone the Repository

```bash
git clone https://github.com/YashArote/fastapi-cpp.git
cd fastapi-cpp
```

---

## 2. Build the Library

You can build the project in **Debug** or **Release** mode using CMake. This creates the library.


```powershell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

---

## 3. Install the Library Globally

You can install it system-wide (e.g., `/usr/local` on Linux/macOS or `C:/Program Files` on Windows).

**Cross-Platform Installation:**
```bash
cmake --install .
```

If you want to specify a custom installation path:
```bash
cmake --install . --prefix "path/to/install/dir"
```

Installed locations (default):
- **Headers:** `<prefix>/include/fastapi-cpp`
- **Library:** `<prefix>/lib/fastapi-cpp.a` (or `.lib` on Windows)

---

## 4. Linking in Another Project

Once installed, FastAPI-CPP can be found automatically using `find_package()`.

### Example `CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.15)
project(MyApp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(FastAPI-CPP REQUIRED)

add_executable(my_app simple_example.cpp)
target_link_libraries(my_app FastAPI_CPP::fastapi-cpp)
```
### Example `simple_example.cpp`
```cpp
#include <fastapi-cpp/server.hpp>
#include <fastapi-cpp/macros.hpp>

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
A more comprehensive example can be found [examples](examples/simple_example.cpp)
### Build and Run
```powershell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
./my_app.exe
```
---

## 🙏 Acknowledgements

This project builds on:

- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [nlohmann/json](https://github.com/nlohmann/json)
