#pragma once
#include <string>
#include <optional>
#include "json.hpp"

using json = nlohmann::json;

struct Request
{
    std::string method;
    std::string path;
    std::optional<json> json_body;
};
