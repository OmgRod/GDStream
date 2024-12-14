using namespace cocos2d;

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
    void onProfile(CCObject*);
    void keyBackClicked() override;

private:
    int m_userID;
};
