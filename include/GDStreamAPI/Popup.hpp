#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace gdstream {
    class Popup : public CCLayer {
    public:
        static Popup* create(const std::string& title, float width, float height) {
            auto ret = new Popup();
            if (ret && ret->init(title, width, height)) {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }

        void show() {
            auto scene = CCDirector::sharedDirector()->getRunningScene();
            this->setZOrder(scene->getHighestChildZ() + 1);
            scene->addChild(this);

            // Initially set the scale of the popup to 0
            this->setScale(0);

            // Create the scale animation with a bounce effect that lasts for 0.5 seconds
            auto scaleTo = CCScaleTo::create(0.2f, 1.0f); // 0.5 seconds duration
            auto bounce = CCEaseSineOut::create(scaleTo); // Apply bounce effect

            // Run the animation on the popup
            this->runAction(bounce);
        }

        bool init(const std::string& title, float width, float height) {
            if (!CCLayer::init()) {
                return false;
            }

            // Get the window size and compute the center position
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            auto winSizeHalf = ccp(winSize.width / 2, winSize.height / 2);
            
            auto fadeBG = CCScale9Sprite::create("popupBG.png"_spr);
            fadeBG->setContentSize(winSize);
            fadeBG->setPosition(winSizeHalf);
            this->addChild(fadeBG);

            // Create the content layer inside the popup
            auto contentLayer = CCLayer::create();
            contentLayer->setContentSize({ width, height });
            contentLayer->setPosition({ 0, 0 });
            contentLayer->setID("contents");
            contentLayer->setZOrder(1);
            this->addChild(contentLayer);

            // Create the background sprite (same as the popup's background)
            auto bg = CCScale9Sprite::create("GJ_square01.png");
            bg->setContentSize({ width, height });
            bg->setPosition(winSizeHalf);
            contentLayer->setID("background");
            contentLayer->addChild(bg);

            // Add the title label to the content layer
            auto titleLabel = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
            titleLabel->setPosition(ccp(winSizeHalf.x, winSizeHalf.y + 50)); // Position relative to content layer
            bg->setID("title");
            contentLayer->addChild(titleLabel);

            return true;
        }
    };
}