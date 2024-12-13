#pragma once

#include <string>

class Stream {
public:
    static bool init(int accID, const std::string& streamName);
};
