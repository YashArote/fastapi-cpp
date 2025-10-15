#pragma once
#include <string>
#include <optional>
#include <map>
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;

struct Response {
    int status_code;
    std::map<std::string, std::string> headers;
    std::string content_type;
    std::string raw_body;
    std::optional<json> json_body;

    // Constructors
    Response(const std::string& body, const std::string& type = "text/plain", int status = 200);
    Response(const char* body, const std::string& type = "text/plain", int status = 200);
    Response(const json& j, const std::string& type = "application/json", int status = 200);

    // Methods
    std::string dump() const;
    void set_header(const std::string& name, const std::string& value);
    std::string get_header(const std::string& name) const;
};
