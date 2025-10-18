#pragma once
#include "binding.hpp"

#define APP_GET(path, func, ...) \
    app.add_route("GET", path, make_handler<__VA_ARGS__>(func))

#define APP_POST(path, func, ...) \
    app.add_route("POST", path, make_handler<__VA_ARGS__>(func))

#define APP_PUT(path, func, ...) \
    app.add_route("PUT", path, make_handler<__VA_ARGS__>(func))

#define APP_PATCH(path, func, ...) \
    app.add_route("PATCH", path, make_handler<__VA_ARGS__>(func))

#define APP_DELETE(path, func, ...) \
    app.add_route("DELETE", path, make_handler<__VA_ARGS__>(func))

#define APP_OPTIONS(path, func, ...) \
    app.add_route("OPTIONS", path, make_handler<__VA_ARGS__>(func))
