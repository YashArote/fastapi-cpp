#pragma once
#include "../include/db_config.hpp"
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;

class RedisPrimitives {
public:
    static bool initialize(const DBConfig& config);
    static void shutdown();
    static bool set(const std::string& key, const std::string& value, int ttl = -1);
    static std::optional<std::string> get(const std::string& key);
    static bool del(const std::string& key);
    static bool exists(const std::string& key);
    static bool setJson(const std::string& key, const json& value, int ttl = -1);
    static std::optional<json> getJson(const std::string& key);
    static bool expire(const std::string& key, int ttl);
    static bool flushDb();
    static bool isConnected();
};
