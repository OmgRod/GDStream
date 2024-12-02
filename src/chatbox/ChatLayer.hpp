#pragma once

#include <Geode/Geode.hpp>
#include <Geode/cocos/layers_scenes_transitions_nodes/CCScene.h>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class ChatLayer : public CCLayer {
public:
    struct Fields {
        EventListener<web::WebTask> m_listener;
    };

    static CCScene* scene();
    static ChatLayer* create();

    bool init();

private:
    geode::EventListener<web::WebTask> m_listener;
};