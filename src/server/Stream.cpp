#include "Stream.hpp"
#include "config.hpp"
#include <Geode/Geode.hpp>
#include <libavformat/avformat.h>

using namespace geode::prelude;

bool Stream::init(int accID, const std::string& streamName) {
    std::string endpoint = ServerConfig::get()->m_serverEndpoint;
    log::debug("Initializing Stream: Account ID = {}, Stream Name = {}, Endpoint = {}", accID, streamName, endpoint);
    return true;
}

$execute {
    auto accountID = GJAccountManager::sharedState()->m_accountID;
    Stream::init(accountID, "Test Livestream");
}
