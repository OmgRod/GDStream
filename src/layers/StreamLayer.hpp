#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class StreamLayer : public CCLayer {
public:
    bool init();
    void onBack(CCObject*);
    void onSettings(CCObject*);
    void onCreate(CCObject*);
    void keyBackClicked() override;
    static StreamLayer* create();
    static CCScene* scene();
};
