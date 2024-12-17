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

            // Get the "contents" node
            auto contents = this->getChildByID("contents");
            if (!contents) {
                log::debug("Error: 'contents' node not found.");
                return;
            }

            // Initially scale contents to 0
            contents->setScale(0);

            // Animate "contents" with a bounce effect
            auto scaleTo = CCScaleTo::create(0.2f, 1.0f);
            auto bounce = CCEaseBackOut::create(scaleTo);
            contents->runAction(bounce);
        }

        bool init(const std::string& title, float width, float height) {
            if (!CCLayer::init()) {
                return false;
            }

            auto winSize = CCDirector::sharedDirector()->getWinSize();

            // Black fade background
            auto fadeBG = CCLayerColor::create(ccc4(0, 0, 0, 150));
            fadeBG->setContentSize(winSize);
            fadeBG->setPosition({0, 0});
            this->addChild(fadeBG, 0); // Behind everything

            // Contents layer (centered in the screen)
            auto contents = CCLayer::create();
            contents->setContentSize({width, height});
            contents->setAnchorPoint(ccp(0.5f, 0.5f)); // Center anchor point
            contents->setPosition(ccp(winSize.width / 2, winSize.height / 2)); // Center of the screen
            contents->setID("contents");
            this->addChild(contents, 1);

            // Popup background
            auto bg = CCScale9Sprite::create("GJ_square01.png");
            bg->setContentSize({width, height});
            bg->setAnchorPoint(ccp(0.5f, 0.5f)); // Center anchor point
            bg->setPosition(ccp(width / 2, height / 2)); // Center it within the contents layer
            contents->addChild(bg);

            // Title label (top-center of the popup background)
            auto titleLabel = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
            titleLabel->setAnchorPoint(ccp(0.5f, 1.0f)); // Center horizontally, align to the top
            titleLabel->setPosition(ccp(width / 2, height - 10)); // Slight offset from the top
            contents->addChild(titleLabel);

            return true;
        }
    };
}
