#pragma once

#include <string>

class ServerConfig {
public:
    std::string m_serverEndpoint = "https://gdstream.omgrod.me/";

    static ServerConfig* get() {
        static ServerConfig instance;
        return &instance;
    }

private:
    ServerConfig() = default;
    ServerConfig(const ServerConfig&) = delete;
    ServerConfig& operator=(const ServerConfig&) = delete;
};
