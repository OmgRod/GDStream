#include "ChatMessage.hpp"
#include <string>
#include <map>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

std::string chatFontName;

ChatMessage::ChatMessage() {}

ChatMessage::~ChatMessage() {}

ChatMessage* ChatMessage::create(const std::string& message, const std::string& username) {
    ChatMessage* ret = new ChatMessage();
    if (ret && ret->init(message, username)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void ChatMessage::openProfile(CCObject*) {
    ProfilePage::create(this->m_userID, false)->show();
}

bool ChatMessage::init(const std::string& message, const std::string& username) {
    if (!CCNode::init()) {
        return false;
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    this->setAnchorPoint({ 0.f, 0.f });
    this->setContentSize({ winSize.width * 0.3f, winSize.height * 0.1f });
    this->setPosition({ winSize.width * 0.f, winSize.height * 0.f });

    float contentHeight = this->getContentHeight();
    float spriteSize = contentHeight * 0.85f;
    float padding = contentHeight * 0.075f;
    float cornerRadius = spriteSize * 0.15f;

    m_userID = GJAccountManager::sharedState()->m_accountID;

    std::map<std::string, std::string> fontMap = {
        {"Montserrat", "montserrat"},
        {"Arial", "arial"},
        {"Comic Sans MS", "comicsans"},
        {"Source Sans Pro", "sourcesanspro"}
    };

    auto chatFont = Mod::get()->getSettingValue<std::string>("chat-font");
    chatFontName = fontMap.count(chatFont) ? fontMap[chatFont] : "defaultfont";

    std::string fontFileRegular = fmt::format("{}.fnt"_spr, chatFontName);

    m_chatMessage = TextArea::create(
        message.c_str(),
        fontFileRegular.c_str(),
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

    std::string fontFileBold = fmt::format("{}-bold.fnt"_spr, chatFontName);

    m_username = CCLabelBMFont::create(username.c_str(), fontFileBold.c_str());
    auto usernameBtn = CCMenuItemSpriteExtra::create(m_username, this, menu_selector(ChatMessage::openProfile));
    if (usernameBtn) {
        usernameBtn->setAnchorPoint({ 0.f, 0.f });

        auto menu = CCMenu::createWithItem(usernameBtn);
        menu->setAnchorPoint({ 0.f, 0.f });
        menu->setPosition({
            spriteSize + padding * 2,
            padding + messageHeight
        });

        this->addChild(menu);
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
