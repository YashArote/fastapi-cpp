#include <iostream>
#include "httplib.h"
#include "core/response.h"
#include "core/request.h"
#include "core/router.h"
#include "core/macros.h"
#include "core/validation.h"

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

    httplib::Server svr;

    svr.Get(R"(.*)", [](const httplib::Request &req, httplib::Response &res) {
        Response app_res = app.handle_request("GET", req.path);
        res.set_content(app_res.dump(), app_res.content_type);
    });

    svr.Post(R"(.*)", [](const httplib::Request &req, httplib::Response &res) {
        std::optional<json> parsed;
        try {
            if (!req.body.empty()) parsed = json::parse(req.body);
        } catch (...) {
            res.status = 400;
            res.set_content("{\"error\":\"Invalid JSON\"}", "application/json");
            return;
        }
        Response app_res = app.handle_request("POST", req.path, parsed);
        res.set_content(app_res.dump(), app_res.content_type);
    });

    std::cout << "Server running at http://localhost:9006\n";
    svr.listen("127.0.0.1", 9006);
}
