/*
#include <Geode/Geode.hpp>
#include <Geode/modify/CCScene.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "ChatButton.hpp"

using namespace geode::prelude;

bool initialized = false;

ChatButton* ChatButton::instance = nullptr;

ChatButton* ChatButton::get() {
    if (instance) return instance;
    auto ret = new ChatButton();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    } else {
        delete ret;
        return nullptr;
    }
}

bool ChatButton::init() {
    if (!CCMenu::init()) {
        return false;
    }

    scheduleUpdate();

    instance = this;

    m_sprite = CircleButtonSprite::create(
        CCSprite::create("chatIcon01.png"_spr),
        CircleBaseColor::Green,
        CircleBaseSize::MediumAlt
    );
    m_sprite->setScale(0.4f);
    m_sprite->setID("sprite");
    addChild(m_sprite);
    setContentSize(m_sprite->getScaledContentSize());
    m_sprite->setPosition(getContentSize() / 2);

    setZOrder(9999998);

    // Declare and use x and y for positioning the button
    float x = 0.0f;
    float y = 0.0f;
    x = std::clamp(x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
    y = std::clamp(y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
    setPosition({x, y});

    return true;
}

void ChatButton::registerWithTouchDispatcher() {
    CCTouchDispatcher::get()->addTargetedDelegate(this, -9999999, true);
}

bool ChatButton::ccTouchBegan(CCTouch* touch, CCEvent* evt) {
    if (!isVisible())
        return false;
    diff = getPosition() - touch->getLocation();
    startPos = new CCPoint(touch->getLocation());
    if (getScaledContentSize().width / 2 < ccpDistance(m_sprite->getPosition(),
        convertToNodeSpace(touch->getLocation()))) {
        return false;
    }
    move = false;
    stopAllActions();
    runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale * m_multiplier)));
    return true;
}

void ChatButton::ccTouchEnded(CCTouch* touch, CCEvent* evt) {
    stopAllActions();
    runAction(CCEaseSineOut::create(CCScaleTo::create(0.3f, m_scale)));
    if (move)
        return;
}

void ChatButton::ccTouchMoved(CCTouch* touch, CCEvent* evt) {
    if (!move)
        if (ccpDistance(*startPos, touch->getLocation()) > 3)
            move = true;
    if (move) {
        auto pos = touch->getLocation() + diff;
        pos.x = std::clamp(pos.x, -getContentWidth() / 2, CCDirector::get()->getWinSize().width - getContentWidth() / 2);
        pos.y = std::clamp(pos.y, -getContentHeight() / 2, CCDirector::get()->getWinSize().height - getContentHeight() / 2);
        setPosition(pos);
    }
}

void ChatButton::update(float dt) {
    setVisible(true);
}

class $modify(MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;
        if (!initialized) {
            ChatButton::get();
            initialized = true;
        }
        return true;
    }
};

class $modify(CCScene) {
    // Fix method signature for getHighestChildZ
    int getHighestChildZ() override {
        int btnZ = -1;
        auto btn = ChatButton::get();
        if (btn) {
            btnZ = btn->getZOrder();
            btn->setZOrder(-1);
        }
        auto highest = CCScene::getHighestChildZ();
        if (btn) btn->setZOrder(btnZ);
        return highest;
    }
};
*/