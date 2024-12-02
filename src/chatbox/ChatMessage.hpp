#ifndef CHATMESSAGE_HPP
#define CHATMESSAGE_HPP

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ChatMessage : public CCNode {
public:
    ChatMessage();
    virtual ~ChatMessage();

    static ChatMessage* create(const std::string& message);

    bool init(const std::string& message);

private:
    CCLabelTTF* m_label;
    CCLabelBMFont* m_chatMessage;
};

#endif
