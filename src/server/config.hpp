#pragma once

#include <string>

class ServerConfig {
public:
    std::string m_serverEndpoint = "127.0.0.1:6942";

    static ServerConfig* get() {
        static ServerConfig instance;
        return &instance;
    }

private:
    ServerConfig() = default;
    ServerConfig(const ServerConfig&) = delete;
    ServerConfig& operator=(const ServerConfig&) = delete;
};
