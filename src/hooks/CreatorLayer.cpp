#include "Geode/cocos/cocoa/CCObject.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

#include "../layers/StreamLayer.hpp"

using namespace geode::prelude;

class $modify(MyCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) {
            return false;
        }

        
        if (auto menu = this->getChildByID("creator-buttons-menu")) {
            auto cameraBtn = CategoryButtonSprite::create(
                CCSprite::create("cameraIcon01.png"_spr),
                CategoryBaseColor::Green,
                CategoryBaseSize::Big
            );

            cameraBtn->setScale();

            auto chatButton = CCMenuItemSpriteExtra::create(
                cameraBtn,
                this,
                menu_selector(MyCreatorLayer::onButtonClick)
            );

            chatButton->setID("stream-button");

            menu->addChild(chatButton);
            menu->updateLayout();   
        }

        return true;
    }

    void onButtonClick(CCObject* sender) {
        auto scene = StreamLayer::scene();
        auto transition = CCTransitionFade::create(0.5f, scene);
        CCDirector::sharedDirector()->pushScene(transition);
    }
};