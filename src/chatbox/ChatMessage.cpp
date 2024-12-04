#include "ChatMessage.hpp"

ChatMessage::ChatMessage()
    : m_label(nullptr) {}

ChatMessage::~ChatMessage() {
    if (m_label) {
        m_label->removeFromParent();
        m_label->release();
    }
}

ChatMessage* ChatMessage::create(const std::string& message, const std::string& username) {
    ChatMessage* ret = new ChatMessage();
    if (ret && ret->init(message, username)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool ChatMessage::init(const std::string& message, const std::string& username) {
    if (!CCNode::init()) {
        return false;
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    this->setAnchorPoint({ 0.f, 0.f });
    this->setContentSize({ winSize.width * 0.3f, winSize.height * 0.1f });
    this->setPosition({ winSize.width * 0.65f, winSize.height * 0.05f });

    float contentHeight = this->getContentHeight();
    float spriteSize = contentHeight * 0.85f;
    float padding = contentHeight * 0.075f;
    float cornerRadius = spriteSize * 0.15f; // 15% corner radius

    m_chatMessage = TextArea::create(
        message.c_str(), // The actual message
        "montserrat.fnt"_spr,
        1.f,
        (winSize.width * 0.3f) - (spriteSize + padding * 3),
        { 0.f, 0.f },
        winSize.height * 0.05,
        false
    );

    if (m_chatMessage) {
        m_chatMessage->setAnchorPoint({ 0.f, 0.f });
        m_chatMessage->setPosition({
            spriteSize + padding * 2,
            padding
        });
        m_chatMessage->setID("message");
        m_chatMessage->setContentWidth((winSize.width * 0.3f) - (spriteSize + padding * 3));
        this->addChild(m_chatMessage);
    }

    float messageHeight = m_chatMessage->getContentHeight() + winSize.height * 0.05;

    m_username = CCLabelBMFont::create(username.c_str(), "montserrat-bold.fnt"_spr);
    if (m_username) {
        m_username->setAnchorPoint({ 0.f, 0.f });

        m_username->setPosition({
            spriteSize + padding * 2,
            padding + messageHeight
        });

        m_username->setID("username");
        this->addChild(m_username);
    }

    CCSprite* pfp = CCSprite::create("unkProfilePicture.png"_spr);
    if (pfp) {
        float scaleX = spriteSize / pfp->getContentSize().width;
        float scaleY = spriteSize / pfp->getContentSize().height;
        pfp->setScaleX(scaleX);
        pfp->setScaleY(scaleY);

        pfp->setAnchorPoint({ 0.f, 0.f });

        pfp->setPosition({
            padding, 
            m_username->getPosition().y - (this->getContentHeight() + m_username->getContentHeight())
        });

        this->addChild(pfp);
    }

    return true;
}
