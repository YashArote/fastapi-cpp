#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <tuple>
#include <sstream>
#include <optional>
#include "httplib.h"
#include "json.hpp" // nlohmann::json

using json = nlohmann::json;

// ---------------- Response ----------------
struct Response
{
    std::string content_type = "text/plain";

    std::string raw_body;
    std::optional<json> json_body;

    // Construct from std::string
    Response(const std::string &body, const std::string &type = "text/plain")
        : content_type(type), raw_body(body) {}

    // Construct from char* (C string)
    Response(const char *body, const std::string &type = "text/plain")
        : content_type(type), raw_body(body) {}

    // Construct from JSON
    Response(const json &j, const std::string &type = "application/json")
        : content_type(type), json_body(j) {}

    std::string dump() const
    {
        if (json_body.has_value())
        {
            return json_body->dump();
        }
        return raw_body;
    }
};

// ---------------- Router ----------------
class Router
{
public:
    using Value = std::vector<std::string>;
    using Handler = std::function<Response(const Value &)>;

    void add_route(const std::string &method, const std::string &template_path, Handler handler)
    {
        routes.push_back({method, template_path, handler});
    }

    Response handle_request(const std::string &method, const std::string &path) const
    {
        for (const auto &route : routes)
        {
            Value values;
            if (route.method == method && match_and_extract(route.template_path, path, values))
            {
                return route.handler(values);
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

    bool match_and_extract(const std::string &tpl, const std::string &path, Value &out_params) const
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

Router app;

// ---------------- Param Parser ----------------
template <typename T>
T parse_param(const std::string &s);

template <>
int parse_param<int>(const std::string &s) { return std::stoi(s); }
template <>
float parse_param<float>(const std::string &s) { return std::stof(s); }
template <>
double parse_param<double>(const std::string &s) { return std::stod(s); }
template <>
std::string parse_param<std::string>(const std::string &s) { return s; }

template <typename T>
std::optional<T> parse_optional(const std::string &s)
{
    if (s.empty())
        return std::nullopt;
    return parse_param<T>(s);
}

// ---------------- Call Helpers ----------------
template <typename Func, typename... Args, std::size_t... I>
Response call_with_params(Func f, const Router::Value &params,
                          std::index_sequence<I...>)
{
    return f(parse_param<Args>(params[I])...);
}

template <typename... Args, typename Func>
Router::Handler make_handler(Func f)
{
    return [f](const Router::Value &params) -> Response
    {
        if (params.size() != sizeof...(Args))
        {
            throw std::runtime_error("Parameter count mismatch");
        }
        return call_with_params<Func, Args...>(f, params,
                                               std::index_sequence_for<Args...>{});
    };
}

// ---------------- Macros (FastAPI style) ----------------
#define APP_GET(path, func, ...) \
    app.add_route("GET", path, make_handler<__VA_ARGS__>(func))

#define APP_POST(path, func, ...) \
    app.add_route("POST", path, make_handler<__VA_ARGS__>(func))

// ---------------- Example Handlers ----------------
Response read_item(int item_id)
{
    return Response(json{{"item_id", item_id}});
}

Response read_user(std::string name, int id)
{
    return Response(json{{"name", name}, {"id", id}});
}

Response serve_html()
{
    return Response("<h1>Hello, World!</h1>", "text/html");
}

// ---------------- Main ----------------
int main()
{
    std::cout << "main started\n"
              << std::flush;

    // Register routes (FastAPI style)
    APP_GET("/items/{item_id}", read_item, int);
    APP_GET("/users/{name}/{id}", read_user, std::string, int);
    APP_GET("/hello/html", serve_html);

    httplib::Server svr;
    svr.Get(R"(.*)", [](const httplib::Request &req, httplib::Response &res)
            {
        Response app_res = app.handle_request("GET", req.path);
        res.set_content(app_res.dump(), app_res.content_type); });

    std::cout << "Server running at http://localhost:9006\n"
              << std::flush;
    svr.listen("127.0.0.1", 9006);
}
