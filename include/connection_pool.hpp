#pragma once
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename ConnectionType>
class ConnectionPool {
public:
    ConnectionPool(int size);
    std::shared_ptr<ConnectionType> acquire();
    void release(std::shared_ptr<ConnectionType> conn);
    bool isHealthy();
    void shutdown();

private:
    std::queue<std::shared_ptr<ConnectionType>> available;
    std::mutex mutex;
    std::condition_variable cv;
    int pool_size;
};
