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

## 📦 Installation

Clone the repo and add `include/` to your project’s include path:

```bash
g++ -std=c++17 main.cpp -Iinclude -o app -lws2_32   # Windows
g++ -std=c++17 main.cpp -Iinclude -o app             # Linux / macOS
```

Then in your code:

```cpp
#include "fastapi_cpp.h"
```

---

## 🚀 Quick Start

### GET route

```cpp
Response read_item(int item_id) {
    return Response(json{{"item_id", item_id}});
}

APP_GET("/items/{item_id}", read_item, Path<int>);
```

### POST route with model

```cpp
struct UserModel {
    std::string name;
    int age;
    MODEL(UserModel, name, age);
};

Response create_user(UserModel user) {
    return Response(json{{"name", user.name}, {"age", user.age}});
}

APP_POST("/users", create_user, Body<UserModel>);
```

### HTML response

```cpp
Response serve_html() {
    return Response("<h1>Hello, World!</h1>", "text/html");
}

APP_GET("/hello", serve_html);
```

### DELETE route

```cpp
Response delete_user(int id) {
    return Response("Deleted user " + std::to_string(id), "text/plain");
}

APP_DELETE("/users/{id}", delete_user, Path<int>);
```

---

## 📝 Full Example

```cpp
#include "fastapi_cpp.h"

Router app;

struct UserModel : public Validatable {
    std::string name;
    int age;
    MODEL(UserModel, name, age);

    void validate() const override {
        if (name.empty()) throw std::runtime_error("Name cannot be empty");
        if (age < 0) throw std::runtime_error("Age must be non-negative");
    }
};

Response read_item(int item_id) {
    return Response(json{{"item_id", item_id}});
}

Response read_user(std::string name, int id) {
    return Response(json{{"name", name}, {"id", id}});
}

Response create_user(UserModel user) {
    user.validate()
    return Response(json{{"name", user.name}, {"age", user.age}});
}

Response update_user(int id, UserModel user) {
    user.validate()
    return Response(json{{"id", id}, {"name", user.name}, {"age", user.age}});
}

Response delete_user(int id) {
    return Response("Deleted user " + std::to_string(id), "text/plain");
}

int main() {
    APP_GET("/items/{item_id}", read_item, Path<int>);
    APP_GET("/users/{name}/{id}", read_user, Path<std::string>, Path<int>);
    APP_POST("/users", create_user, Body<UserModel>);
    APP_PUT("/users/{id}", update_user, Path<int>, Body<UserModel>);
    APP_DELETE("/users/{id}", delete_user, Path<int>);

    FastApiCpp::run(app, "127.0.0.1", 8080);
}
```

---

## 🙏 Acknowledgements

This project builds on:

- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [nlohmann/json](https://github.com/nlohmann/json)

---

