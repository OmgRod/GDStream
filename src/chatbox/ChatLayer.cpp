#include "ChatLayer.hpp"
#include "ChatMessage.hpp"

CCScene* ChatLayer::scene() {
    auto scene = CCScene::create();
    scene->addChild(ChatLayer::create());
    return scene;
}

ChatLayer* ChatLayer::create() {
    ChatLayer* ret = new ChatLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool ChatLayer::init() {
    if (!CCLayer::init())
        return false;

    this->setID("ChatLayer");

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    CCScale9Sprite* background = CCScale9Sprite::create("chatSquare_01.png"_spr);
    background->setContentSize({ winSize.width * 0.3f, winSize.height * 0.9f });
    background->setPosition({ winSize.width * 0.65f, winSize.height * 0.05f });
    background->setAnchorPoint({ 0.f, 0.f });
    background->setID("background");

    auto clippingNode = CCClippingNode::create();
    clippingNode->setStencil(background);
    clippingNode->setAlphaThreshold(0.1f);

    clippingNode->addChild(background);

    // auto label = CCLabelBMFont::create("Chat Message", "montserrat.fnt"_spr);
    // label->setPosition({ background->getContentSize().width / 2, background->getContentSize().height / 2 });
    // clippingNode->addChild(label);

    ChatMessage* msg = ChatMessage::create("Test Message Test Message Test Message", GameManager::sharedState()->m_playerName.c_str());
    clippingNode->addChild(msg);

    this->addChild(clippingNode);

    return true;
}