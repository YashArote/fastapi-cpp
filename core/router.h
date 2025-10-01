#pragma once
#include <string>
#include <vector>
#include <functional>
#include "request.h"
#include "response.h"

class Router
{
public:
    using Values = std::vector<std::string>;
    using Handler = std::function<Response(const Request &, const Values &)>;

    void add_route(const std::string &method, const std::string &template_path, Handler handler)
    {
        routes.push_back({method, template_path, handler});
    }

    Response handle_request(const std::string &method,
                            const std::string &path,
                            const std::optional<json> &body = std::nullopt) const
    {
        for (const auto &route : routes)
        {
            Values values;
            if (route.method == method && match_and_extract(route.template_path, path, values))
            {
                Request req{method, path, body};
                return route.handler(req, values);
            }
        }
        return Response("404 Not Found", "text/plain");
    }

private:
    struct Route
    {
        std::string method;
        std::string template_path;
        Handler handler;
    };
    std::vector<Route> routes;

    bool match_and_extract(const std::string &tpl, const std::string &path, Values &out_params) const
    {
        size_t i = 0, j = 0;
        while (i < tpl.size() && j < path.size())
        {
            if (tpl[i] == '{')
            {
                size_t end = tpl.find('}', i);
                if (end == std::string::npos)
                    return false;

                i = end + 1;
                size_t next_slash = path.find('/', j);
                std::string value;
                if (next_slash == std::string::npos)
                {
                    value = path.substr(j);
                    j = path.size();
                }
                else
                {
                    value = path.substr(j, next_slash - j);
                    j = next_slash;
                }
                out_params.push_back(value);
            }
            else
            {
                if (tpl[i] != path[j])
                    return false;
                ++i;
                ++j;
            }
        }
        return i == tpl.size() && j == path.size();
    }
};
