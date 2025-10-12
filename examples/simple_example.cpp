#include "server.hpp"
#include "macros.hpp"
#include "validation.hpp"
#include <iostream>

using json = nlohmann::json;

Router app;

struct UserModel : public Validatable {
    std::string name;
    int age;
    MODEL(UserModel, name, age);
    void validate() const override {
        if (name.empty()) {
            throw std::runtime_error("Name cannot be empty");
        }
        if (age < 0) {
            throw std::runtime_error("Age must be non-negative");
        }
    }
};

Response get_hello() {
    return Response(json{
        {"message", "Hello from FastAPI-C++!"},
        {"version", "1.0.0"}
    });
}

Response get_user(int user_id) {
    return Response(json{
        {"id", user_id},
        {"name", "User " + std::to_string(user_id)},
        {"message", "This is a sample user"}
    });
}

Response create_user(UserModel user) {
    user.validate();
    return Response(json{
        {"id", 123},
        {"name", user.name},
        {"age", user.age},
        {"message", "User created successfully"}
    });
}

Response get_html() {
    std::string html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>FastAPI-C++ Simple Example</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; }
        .endpoint { background: #f5f5f5; padding: 10px; margin: 10px 0; border-radius: 5px; }
        .method { font-weight: bold; color: #007bff; }
        .path { font-family: monospace; }
    </style>
</head>
<body>
    <h1>🚀 FastAPI-C++ Simple Example</h1>
    <p>This is a minimal example showing basic FastAPI-C++ features.</p>
    
    <h2>Available Endpoints:</h2>
    
    <div class="endpoint">
        <span class="method">GET</span> <span class="path">/</span> - Hello message
    </div>
    
    <div class="endpoint">
        <span class="method">GET</span> <span class="path">/users/{id}</span> - Get user by ID
    </div>
    
    <div class="endpoint">
        <span class="method">POST</span> <span class="path">/users</span> - Create a new user
    </div>
    
    <div class="endpoint">
        <span class="method">GET</span> <span class="path">/demo</span> - This HTML page
    </div>
    
    <h2>Try the API:</h2>
    <p>Use curl or any HTTP client to test the endpoints:</p>
    <pre>
# Get hello message
curl http://127.0.0.1:8080/

# Get user by ID
curl http://127.0.0.1:8080/users/123

# Create a new user
curl -X POST http://127.0.0.1:8080/users \
  -H "Content-Type: application/json" \
  -d '{"name":"John Doe","age":30}'
    </pre>
</body>
</html>
    )";
    return Response(html, "text/html");
}

int main() {
    std::cout << "🚀 Starting FastAPI-C++ Simple Example..." << std::endl;
    
    APP_GET("/", get_hello);
    APP_GET("/users/{id}", get_user, Path<int>);
    APP_POST("/users", create_user, Body<UserModel>);
    APP_GET("/demo", get_html);
    
    std::cout << "Registered " << app.get_route_count() << " routes" << std::endl;
    std::cout << "Server will be available at: http://127.0.0.1:8080" << std::endl;
    std::cout << "Try the demo page at: http://127.0.0.1:8080/demo" << std::endl;
    
    FastApiCpp::run(app, "127.0.0.1", 8080);
    
    return 0;
}
