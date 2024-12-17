#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/ui/Layout.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/utils/web.hpp>
#include "StreamCreatorLayer.hpp"
#include "StreamLayer.hpp"

#include <gd-addons/GDAddons.hpp>

using namespace geode::prelude;
using namespace gdaddons;

StreamLayer::StreamLayer() = default;
StreamLayer::~StreamLayer() = default;

void StreamLayer::onBack(CCObject*) {
    StreamLayer::keyBackClicked();
}

void StreamLayer::onSettings(CCObject*) {
    openSettingsPopup(Mod::get());
}

void StreamLayer::onCreate(CCObject*) {
    // FLAlertLayer::create("GDStream", "This feature is coming soon!", "OK")->show();
    auto scene = StreamCreatorLayer::scene();
    auto transition = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(transition);
}

void StreamLayer::onKofiClicked(CCObject*) {
    geode::utils::web::openLinkInBrowser("https://ko-fi.com/omgrod");
}

void StreamLayer::onKofi(CCObject*) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto popup = gdaddons::Popup::create("Support me on Ko-Fi!", winSize.width * 0.7f, winSize.height * 0.8f);
    auto contents = popup->getChildByID("contents");

    auto text = TextArea::create(
        "If you support me, you will get the following benefits:\n- 5 streams on your profile\n- More updates", // The actual message
        "bigFont.fnt",
        0.4f,
        popup->getChildByID("contents")->getContentWidth() - (winSize.width * 0.1),
        { 0.f, 0.f },
        winSize.height * 0.05,
        false
    );
    text->setContentSize({ 0.f, 0.f });
    text->setPosition({ contents->getContentWidth() * 0.1f, contents->getContentHeight() * 0.4f });

    contents->addChild(text);
    
    auto kofiBtnSpr = ButtonSprite::create("Donate!");
    auto kofiBtn = CCMenuItemSpriteExtra::create(
        kofiBtnSpr, this, menu_selector(StreamLayer::onKofiClicked)
    );

    contents->getChildByID("menu")->addChild(kofiBtn);

    popup->show();
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

    auto kofiBtn = CCMenuItemSpriteExtra::create(
        CircleButtonSprite::create(
            CCSprite::create("kofiLogo01.png"_spr),
            CircleBaseColor::Green,
            CircleBaseSize::Tiny
        ),
        this,
        menu_selector(StreamLayer::onKofi)
    );
    kofiBtn->setID("kofi-btn");
    topbar->addChild(kofiBtn);

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