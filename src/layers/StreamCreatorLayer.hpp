using namespace cocos2d;

class StreamCreatorLayer : public CCLayer {
public:
    StreamCreatorLayer();
    virtual ~StreamCreatorLayer();
    bool init() override;
    static StreamCreatorLayer* create();
    static CCScene* scene();
    void onBack(CCObject*);
    void keyBackClicked() override;

private:
    int m_userID;
};
