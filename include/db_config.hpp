#pragma once
#include <string>

struct DBConfig {
    enum DBType { PostgreSQL, MongoDB, None };
    enum CacheType { Redis, CacheNone };
    DBType db_type = None;
    std::string db_host;
    int db_port;
    std::string db_name;
    std::string db_user;
    std::string db_password;
    std::string db_connection_string;
    int db_pool_size = 10;
    bool auto_create_db = true;
    CacheType cache_type = CacheNone;
    std::string cache_host;
    int cache_port = 6379;
    std::string cache_password;
    int cache_db = 0;
    int cache_ttl = 3600;
};
