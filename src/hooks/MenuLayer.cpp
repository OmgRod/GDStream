#include "Geode/cocos/cocoa/CCObject.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

#include "../layers/StreamLayer.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = this->getChildByID("bottom-menu");

        auto cameraBtn = CircleButtonSprite::create(
            CCSprite::create("cameraIcon01.png"_spr),
            CircleBaseColor::Green,
            CircleBaseSize::MediumAlt
        );

        auto chatButton = CCMenuItemSpriteExtra::create(
            cameraBtn,
            this,
            menu_selector(MyMenuLayer::onButtonClick)
        );

        chatButton->setID("stream-button");

        menu->addChild(chatButton);
        menu->updateLayout();

        return true;
    }

    void onButtonClick(CCObject* sender) {
        auto scene = StreamLayer::scene();
        auto transition = CCTransitionFade::create(0.5f, scene);
        CCDirector::sharedDirector()->replaceScene(transition);
    }
};