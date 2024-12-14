#include <Geode/Geode.hpp>
#include "../chatbox/ChatLayer.hpp"

using namespace geode::prelude;

ChatButton::ChatButton() = default;
ChatButton::~ChatButton() = default;

bool ChatButton::init() {
    if (!CCLayer::init()) return false;

    setMouseEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto menu = CCMenu::create();

    

    return true;
}

ChatButton* ChatButton::create() {
    auto layer = new ChatButton();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}