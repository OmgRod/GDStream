#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/ui/Layout.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "StreamLayer.hpp"

using namespace geode::prelude;

void StreamLayer::onBack(CCObject*) {
    StreamLayer::keyBackClicked();
}

void StreamLayer::onSettings(CCObject*) {
    openSettingsPopup(Mod::get());
}

void StreamLayer::onCreate(CCObject*) {
    FLAlertLayer::create("GDStream", "This feature is coming soon!", "OK")->show();
}

bool StreamLayer::init() {
    if (!CCLayer::init()) return false;

    setMouseEnabled(true);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto menu = CCMenu::create();

    this->setAnchorPoint({ 0.5, 0.5 });

    auto corner1 = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    corner1->setPosition(CCPoint(winSize.width * -0.5, winSize.height * -0.5));
    corner1->setAnchorPoint(CCPoint(0, 0));
    corner1->setID("corner1");
    menu->addChild(corner1);

    auto corner2 = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    corner2->setPosition(CCPoint(winSize.width * 0.5, winSize.height * -0.5));
    corner2->setAnchorPoint(CCPoint(1, 0));
    corner2->setFlipX(true);
    corner2->setID("corner2");
    menu->addChild(corner2);

    auto gameBgSpr = CCSprite::create("game_bg_01_001.png");
    gameBgSpr->setScale(2.f);
    gameBgSpr->setZOrder(-1);
    gameBgSpr->setPositionY(winSize.height / -2);
    gameBgSpr->setID("gameBgSpr");
    menu->addChild(gameBgSpr);

    auto squareSpr = CCScale9Sprite::create("GJ_square01.png");
    squareSpr->setPosition(CCPoint(winSize.width * 0, winSize.height * -0.07));
    squareSpr->setContentSize(CCPoint(winSize.width * 0.8, winSize.height * 0.73));
    squareSpr->setID("squareSpr");
    squareSpr->setZOrder(1);
    menu->addChild(squareSpr);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(StreamLayer::onBack)
    );
    backBtn->setPosition(winSize.width * -0.45, winSize.height * 0.4);
    backBtn->setID("back-btn");
    menu->addChild(backBtn);

    auto topbar = CCMenu::create();
    topbar->setContentSize({ winSize.width * 0.5f, winSize.height * 0.075f });
    topbar->setPosition({ winSize.width * 0.6f, winSize.height * 0.9f });
    auto layout = RowLayout::create();
    layout->setAxisAlignment(AxisAlignment::End);
    topbar->setLayout(layout);
    topbar->setID("topbar");

    auto addBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png"),
        this,
        menu_selector(StreamLayer::onCreate)
    );
    addBtn->setID("add-btn");
    topbar->addChild(addBtn);

    auto settingsBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"),
        this,
        menu_selector(StreamLayer::onSettings)
    );
    settingsBtn->setID("settings-btn");
    topbar->addChild(settingsBtn);

    menu->updateLayout();
    this->addChild(menu);

    topbar->updateLayout();
    this->addChild(topbar);

    return true;
}

void StreamLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

StreamLayer* StreamLayer::create() {
    StreamLayer* ret = new StreamLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

CCScene* StreamLayer::scene() {
    auto scene = CCScene::create();
    scene->addChild(StreamLayer::create());
    return scene;
}
