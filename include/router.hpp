#pragma once
#include <string>
#include <vector>
#include <functional>
#include "request.hpp"
#include "response.hpp"

class Router {
public:
    using Values = std::vector<std::string>;
    using Handler = std::function<Response(const Request&, const Values&)>;
    void add_route(const std::string& method, const std::string& template_path, Handler handler);
    Response handle_request(const std::string& method, const std::string& path, const std::optional<json>& body = std::nullopt) const;
    size_t get_route_count() const { return routes.size(); }
private:
    struct Route {
        std::string method;
        std::string template_path;
        Handler handler;
    };
    std::vector<Route> routes;
    bool match_and_extract(const std::string& tpl, const std::string& path, Values& out_params) const;
};
