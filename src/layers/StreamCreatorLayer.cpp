#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/ui/Layout.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "StreamCreatorLayer.hpp"

using namespace geode::prelude;

StreamCreatorLayer::StreamCreatorLayer() = default;
StreamCreatorLayer::~StreamCreatorLayer() = default;

void StreamCreatorLayer::onBack(CCObject*) {
    StreamCreatorLayer::keyBackClicked();
}

bool StreamCreatorLayer::init() {
    if (!CCLayer::init()) return false;

    setMouseEnabled(true);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto menu = CCMenu::create();

    this->setAnchorPoint({ 0.5, 0.5 });

    m_userID = GJAccountManager::sharedState()->m_accountID;

    auto gameBgSpr = CCSprite::create("GJ_gradientBG.png");
    gameBgSpr->setScaleX(50.f);
    gameBgSpr->setScaleY(2.f);
    gameBgSpr->setZOrder(-1);
    gameBgSpr->setColor({ 0, 102, 255 });
    gameBgSpr->setID("gameBgSpr");
    menu->addChild(gameBgSpr);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(StreamCreatorLayer::onBack)
    );
    backBtn->setPosition(winSize.width * -0.45, winSize.height * 0.4);
    backBtn->setID("back-btn");
    menu->addChild(backBtn);

    menu->updateLayout();
    this->addChild(menu);

    return true;
}

void StreamCreatorLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

StreamCreatorLayer* StreamCreatorLayer::create() {
    auto layer = new StreamCreatorLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

CCScene* StreamCreatorLayer::scene() {
    auto scene = CCScene::create();
    auto layer = StreamCreatorLayer::create();
    scene->addChild(layer);
    return scene;
}