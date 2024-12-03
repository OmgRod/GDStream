#include "Geode/cocos/cocoa/CCObject.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

#include "../StreamLayer.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = this->getChildByID("bottom-menu");

        auto chatButton = CCMenuItemSpriteExtra::create(
            CCSprite::create("menuStreamBtn.png"_spr),
            nullptr,
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