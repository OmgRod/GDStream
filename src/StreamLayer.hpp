#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class StreamLayer : public CCLayer {
public:
    bool init();
    static StreamLayer* create();
    static CCScene* scene();
};
