/*
#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class ChatButton : public CCMenu {
protected:
    static ChatButton* instance;

    float m_scale = 1.0f;
    float m_multiplier = 0.8f;
    bool move = false;

    CCPoint* startPos;
    CCPoint diff;

    CCSprite* m_sprite;

    bool init() override;
    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
    void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
    void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
    void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;
    void registerWithTouchDispatcher() override;

public:
    static ChatButton* get();
    void onPress();
    void update(float dt);
};
*/