#include <Geode/Geode.hpp>

using namespace geode::prelude;

class StreamLayer : public CCLayer {
public:
    StreamLayer();
    virtual ~StreamLayer();
    bool init() override;
    static StreamLayer* create();
    static CCScene* scene();
    void onBack(CCObject*);
    void onSettings(CCObject*);
    void onCreate(CCObject*);
    void onKofiClicked(CCObject*);
    void onKofi(CCObject*);
    void onProfile(CCObject*);
    void keyBackClicked() override;

private:
    int m_userID;
};
