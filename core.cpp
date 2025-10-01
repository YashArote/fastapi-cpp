#include <iostream>
#include "fastapi_cpp.h"
Router app;

// ---------------- Models ----------------
struct UserModel : public Validatable {
    std::string name;
    int age;
    MODEL(UserModel, name, age);

    void validate() const override {
        if (name.empty()) throw std::runtime_error("Name cannot be empty");
        if (age < 0) throw std::runtime_error("Age must be non-negative");
    }
};

// ---------------- Handlers ----------------
Response read_item(int item_id) {
    return Response(json{{"item_id", item_id}});
}

Response update_user(int id, UserModel user) {
    user.validate(); // ✅ validation hook
    return Response(json{{"id", id}, {"name", user.name}, {"age", user.age}});
}

// ---------------- Main ----------------
int main() {
    APP_GET("/items/{item_id}", read_item, Path<int>);
    APP_POST("/users/{id}", update_user, Path<int>, Body<UserModel>);
    FastApiCpp::run(app, "127.0.0.1", 8080);    
}
