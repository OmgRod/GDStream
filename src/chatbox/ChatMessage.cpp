#include "ChatMessage.hpp"

ChatMessage::ChatMessage()
    : m_label(nullptr) {}

ChatMessage::~ChatMessage() {
    if (m_label) {
        m_label->removeFromParent();
        m_label->release();
    }
}

ChatMessage* ChatMessage::create(const std::string& message) {
    ChatMessage* ret = new ChatMessage();
    if (ret && ret->init(message)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool ChatMessage::init(const std::string& message) {
    if (!CCNode::init()) {
        return false;
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    this->setAnchorPoint({ 0.f, 0.f });
    this->setContentSize({ winSize.width * 0.3f, winSize.height * 0.1f });
    this->setPosition({ winSize.width * 0.65f, winSize.height * 0.05f });

    // Padding and size calculations
    float contentHeight = this->getContentHeight();
    float spriteSize = contentHeight * 0.85f;
    float padding = contentHeight * 0.05f;
    float cornerRadius = spriteSize * 0.15f; // 15% corner radius

    // Profile picture sprite
    CCSprite* pfp = CCSprite::create("unkProfilePicture.png"_spr);
    if (pfp) {
        // Set the scale to achieve desired size
        float scaleX = spriteSize / pfp->getContentSize().width;
        float scaleY = spriteSize / pfp->getContentSize().height;
        pfp->setScaleX(scaleX);
        pfp->setScaleY(scaleY);

        // Set position with padding
        pfp->setAnchorPoint({ 0.f, 0.f });
    }

    // Chat message label
    m_chatMessage = CCLabelBMFont::create(message.c_str(), "montserrat.fnt"_spr);
    if (m_chatMessage) {
        m_chatMessage->setAnchorPoint({ 0.f, 0.f });
        m_chatMessage->setPosition({ spriteSize + padding * 2, padding });
        this->addChild(m_chatMessage);
    }

    return true;
}
