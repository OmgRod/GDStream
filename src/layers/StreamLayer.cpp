#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/ui/Layout.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "StreamLayer.hpp"

using namespace geode::prelude;

StreamLayer::StreamLayer() = default;
StreamLayer::~StreamLayer() = default;

void StreamLayer::onBack(CCObject*) {
    StreamLayer::keyBackClicked();
}

void StreamLayer::onSettings(CCObject*) {
    openSettingsPopup(Mod::get());
}

void StreamLayer::onCreate(CCObject*) {
    FLAlertLayer::create("GDStream", "This feature is coming soon!", "OK")->show();
}

void StreamLayer::onProfile(CCObject*) {
    auto profile = ProfilePage::create(this->m_userID, true);
    profile->show();
}

bool StreamLayer::init() {
    if (!CCLayer::init()) return false;

    setMouseEnabled(true);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto menu = CCMenu::create();

    this->setAnchorPoint({ 0.5, 0.5 });

    m_userID = GJAccountManager::sharedState()->m_accountID;

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

    auto gameBgSpr = CCSprite::create("GJ_gradientBG.png");
    gameBgSpr->setScaleX(50.f);
    gameBgSpr->setScaleY(2.f);
    gameBgSpr->setZOrder(-1);
    gameBgSpr->setColor({ 0, 102, 255 });
    gameBgSpr->setID("gameBgSpr");
    menu->addChild(gameBgSpr);

    auto squareSpr = CCScale9Sprite::create("GJ_square01.png");
    squareSpr->setPosition(CCPoint(winSize.width * 0, winSize.height * -0.03));
    squareSpr->setContentSize(CCSize(winSize.width * 0.8, winSize.height * 0.77));
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
    topbar->setPosition({ winSize.width * 0.6f, winSize.height * 0.93f });
    auto layout = RowLayout::create();
    layout->setAxisAlignment(AxisAlignment::End);
    topbar->setLayout(layout);
    topbar->setID("topbar");

    auto addBtn = CCMenuItemSpriteExtra::create(
        CircleButtonSprite::create(
            CCSprite::create("plusIcon01.png"_spr),
            CircleBaseColor::Green,
            CircleBaseSize::Tiny
        ),
        this,
        menu_selector(StreamLayer::onCreate)
    );
    addBtn->setID("add-btn");
    topbar->addChild(addBtn);

    auto settingsBtn = CCMenuItemSpriteExtra::create(
        CircleButtonSprite::create(
            CCSprite::create("settingsIcon01.png"_spr),
            CircleBaseColor::Green,
            CircleBaseSize::Tiny
        ),
        this,
        menu_selector(StreamLayer::onSettings)
    );
    settingsBtn->setID("settings-btn");
    topbar->addChild(settingsBtn);

    auto profileBtn = CCMenuItemSpriteExtra::create(
        CircleButtonSprite::create(
            CCSprite::create("accountIcon01.png"_spr),
            CircleBaseColor::Green,
            CircleBaseSize::Tiny
        ),
        this,
        menu_selector(StreamLayer::onProfile)
    );
    profileBtn->setID("profile-btn");
    profileBtn->getChildByType<CircleButtonSprite*>(0)->getChildByType<CCSprite*>(0)->setScale(0.75f);
    topbar->addChild(profileBtn);

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
    auto layer = new StreamLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

CCScene* StreamLayer::scene() {
    auto scene = CCScene::create();
    auto layer = StreamLayer::create();
    scene->addChild(layer);
    return scene;
}