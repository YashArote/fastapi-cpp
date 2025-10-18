#pragma once
#include "db_config.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class MongoPrimitives {
public:
    static bool initialize(const DBConfig& config);
    static bool ensureDatabase(const std::string& dbName);
    static void shutdown();
    static json find(const std::string& collection, const json& filter, const json& options = {});
    static json insertOne(const std::string& collection, const json& document);
    static json insertMany(const std::string& collection, const json& documents);
    static json updateOne(const std::string& collection, const json& filter, const json& update);
    static json updateMany(const std::string& collection, const json& filter, const json& update);
    static json deleteOne(const std::string& collection, const json& filter);
    static json deleteMany(const std::string& collection, const json& filter);
    static json aggregate(const std::string& collection, const json& pipeline);
    static bool createIndex(const std::string& collection, const json& keys);
    static json getConnectionInfo();
    static bool isConnected();
};
