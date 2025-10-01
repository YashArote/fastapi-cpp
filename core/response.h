#pragma once
#include <string>
#include <optional>
#include "json.hpp"

using json = nlohmann::json;

struct Response {
    std::string content_type = "text/plain";
    std::string raw_body;
    std::optional<json> json_body;

    Response(const std::string &body, const std::string &type = "text/plain")
        : content_type(type), raw_body(body) {}

    Response(const char *body, const std::string &type = "text/plain")
        : content_type(type), raw_body(body) {}

    Response(const json &j, const std::string &type = "application/json")
        : content_type(type), json_body(j) {}

    std::string dump() const {
        if (json_body.has_value())
            return json_body->dump();
        return raw_body;
    }
};
