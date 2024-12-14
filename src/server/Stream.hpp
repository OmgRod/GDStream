#pragma once

#include <string>

class Stream {
public:
    // Initializes the stream with the given account ID and stream name
    static bool init(int accID, const std::string& streamName);

    // Starts an RTMP livestream with the specified stream name
    static bool startRTMPStream(const std::string& streamName);
};
