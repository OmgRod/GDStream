#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ChatButton : public CCLayer {
public:
    ChatButton();
    virtual ~ChatButton();
    bool init() override;
    static ChatButton* create();
};
