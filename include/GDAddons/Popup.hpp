#ifndef POPUP_HPP
#define POPUP_HPP

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace gdaddons {
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

            auto contents = this->getChildByID("contents");
            if (!contents) {
                log::debug("Error: 'contents' node not found.");
                return;
            }

            contents->setScale(0);

            auto scaleTo = CCScaleTo::create(0.2f, 1.0f);
            auto bounce = CCEaseBackOut::create(scaleTo);
            contents->runAction(bounce);
        }

        bool init(const std::string& title, float width, float height) {
            if (!CCLayer::init()) {
                return false;
            }

            auto winSize = CCDirector::sharedDirector()->getWinSize();

            auto fadeBG = CCLayerColor::create(ccc4(0, 0, 0, 150));
            fadeBG->setContentSize(winSize);
            fadeBG->setPosition({0, 0});
            this->addChild(fadeBG, 0);

            auto contents = CCLayer::create();
            contents->setContentSize({width, height});
            contents->setAnchorPoint(ccp(0.5f, 0.5f));
            contents->setPosition(ccp(winSize.width / 2, winSize.height / 2));
            contents->setID("contents");
            contents->ignoreAnchorPointForPosition(false);
            this->addChild(contents, 1);

            auto bg = CCScale9Sprite::create("GJ_square01.png");
            bg->setContentSize({width, height});
            bg->setAnchorPoint(ccp(0.5f, 0.5f));
            bg->setPosition(ccp(width / 2, height / 2));
            contents->addChild(bg);

            auto titleLabel = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
            titleLabel->setAnchorPoint(ccp(0.5f, 1.0f));
            titleLabel->setPosition(ccp(width / 2, height - 10));
            contents->addChild(titleLabel);

            return true;
        }
    };
}

#endif // POPUP_HPP
