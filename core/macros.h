#pragma once
#include "binding.h"

#define APP_GET(path, func, ...) \
    app.add_route("GET", path, make_handler<__VA_ARGS__>(func))

#define APP_POST(path, func, ...) \
    app.add_route("POST", path, make_handler<__VA_ARGS__>(func))
