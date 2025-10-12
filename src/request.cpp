#include "../include/request.hpp"

Request::Request(const std::string& method, const std::string& path, const std::optional<json>& body)
    : method(method), path(path), json_body(body) {}

std::string Request::get_header(const std::string& name) const {
    auto it = headers.find(name);
    return it != headers.end() ? it->second : "";
}

std::string Request::get_query_param(const std::string& name) const {
    auto it = query_params.find(name);
    return it != query_params.end() ? it->second : "";
}

std::string Request::get_path_param(const std::string& name) const {
    auto it = path_params.find(name);
    return it != path_params.end() ? it->second : "";
}
