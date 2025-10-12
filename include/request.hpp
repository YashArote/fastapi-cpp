#pragma once
#include <string>
#include <optional>
#include <map>
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;

struct Request {
    std::string method;
    std::string path;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> query_params;
    std::map<std::string, std::string> path_params;
    std::optional<json> json_body;
    std::string raw_body;

    // Constructor
    Request(const std::string& method, const std::string& path, const std::optional<json>& body = std::nullopt);

    // Helper methods
    std::string get_header(const std::string& name) const;
    std::string get_query_param(const std::string& name) const;
    std::string get_path_param(const std::string& name) const;
};
