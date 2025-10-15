#include "../include/response.hpp"

Response::Response(const std::string& body, const std::string& type, int status)
    : status_code(status), content_type(type), raw_body(body) {}

Response::Response(const char* body, const std::string& type, int status)
    : status_code(status), content_type(type), raw_body(body) {}

Response::Response(const json& j, const std::string& type, int status)
    : status_code(status), content_type(type), json_body(j) {}

std::string Response::dump() const {
    if (json_body.has_value())
        return json_body->dump();
    return raw_body;
}

void Response::set_header(const std::string& name, const std::string& value) {
    headers[name] = value;
}

std::string Response::get_header(const std::string& name) const {
    auto it = headers.find(name);
    return it != headers.end() ? it->second : "";
}
