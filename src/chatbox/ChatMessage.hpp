#ifndef CHATMESSAGE_HPP
#define CHATMESSAGE_HPP

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ChatMessage : public CCNode {
public:
    ChatMessage();
    virtual ~ChatMessage();

    static ChatMessage* create(const std::string& message, const std::string& username);

    bool init(const std::string& message, const std::string& username);
    void openProfile(CCObject*);

private:
    CCLabelTTF* m_label;
    TextArea* m_chatMessage;
    CCLabelBMFont* m_username;
    int m_userID;
};

#endif
