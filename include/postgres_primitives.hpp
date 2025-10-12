#pragma once
#include "../include/db_config.hpp"
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;

class PostgresPrimitives {
public:
    static bool initialize(const DBConfig& config);
    static bool ensureDatabase(const std::string& dbName);
    static void shutdown();
    static json executeQuery(const std::string& sql, const json& params = {});
    static json executeTransaction(const std::vector<std::pair<std::string, json>>& queries);
    static json getConnectionInfo();
    static bool isConnected();
};
