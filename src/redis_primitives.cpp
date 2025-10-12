#include "../include/redis_primitives.hpp"
#include <iostream>

bool RedisPrimitives::initialize(const DBConfig& config) {
    std::cout << "Redis primitives initialized" << std::endl;
    return true;
}

void RedisPrimitives::shutdown() {
    std::cout << "Redis primitives shutdown" << std::endl;
}

bool RedisPrimitives::set(const std::string& key, const std::string& value, int ttl) {
    std::cout << "Redis set key: " << key << std::endl;
    return true;
}

std::optional<std::string> RedisPrimitives::get(const std::string& key) {
    std::cout << "Redis get key: " << key << std::endl;
    return std::nullopt;
}

bool RedisPrimitives::del(const std::string& key) {
    std::cout << "Redis del key: " << key << std::endl;
    return true;
}

bool RedisPrimitives::exists(const std::string& key) {
    std::cout << "Redis exists key: " << key << std::endl;
    return false;
}

bool RedisPrimitives::setJson(const std::string& key, const json& value, int ttl) {
    std::cout << "Redis setJson key: " << key << std::endl;
    return true;
}

std::optional<json> RedisPrimitives::getJson(const std::string& key) {
    std::cout << "Redis getJson key: " << key << std::endl;
    return std::nullopt;
}

bool RedisPrimitives::expire(const std::string& key, int ttl) {
    std::cout << "Redis expire key: " << key << std::endl;
    return true;
}

bool RedisPrimitives::flushDb() {
    std::cout << "Redis flushDb" << std::endl;
    return true;
}

bool RedisPrimitives::isConnected() {
    return true;
}
