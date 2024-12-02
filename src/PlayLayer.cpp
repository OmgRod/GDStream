#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "chatbox/ChatLayer.hpp"

using namespace geode::prelude;

ChatLayer* chatLayer = ChatLayer::create();

$execute {
    bool chatEnabled = Mod::get()->getSettingValue<bool>("chat");

    if (chatEnabled) {
        CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();

        chatLayer->setZOrder(9);
		chatLayer->setVisible(false);
        SceneManager::get()->keepAcrossScenes(chatLayer);
    }
}

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        chatLayer->setVisible(true);

        return true;
    }

    void onQuit() {
        if (chatLayer) {
            chatLayer->setVisible(false);
        }

		PlayLayer::onQuit();
    }
};