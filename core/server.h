#pragma once
#include "httplib.h"
#include "router.h"
#include "json.hpp"

using json = nlohmann::json;

class FastApiCpp {
public:
    static void run(Router& app, const std::string& host, int port) {
        httplib::Server svr;

        auto handle_request = [&](const httplib::Request& req, httplib::Response& res) {
            std::optional<json> parsed;
            if (!req.body.empty()) {
                try {
                    parsed = json::parse(req.body);
                } catch (...) {
                    res.status = 400;
                    res.set_content("{\"error\":\"Invalid JSON\"}", "application/json");
                    return;
                }
            }

            Response app_res = app.handle_request(req.method, req.path, parsed);
            res.set_content(app_res.dump(), app_res.content_type);
        };

        svr.Get(R"(.*)", handle_request);
        svr.Post(R"(.*)", handle_request);
        svr.Put(R"(.*)", handle_request);
        svr.Patch(R"(.*)", handle_request);
        svr.Delete(R"(.*)", handle_request);
        svr.Options(R"(.*)", handle_request);

        std::cout << "🚀 Server running at http://" << host << ":" << port << "\n";
        svr.listen(host, port);
    }
};