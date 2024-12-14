#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "layers/chatbox/ChatLayer.hpp"

using namespace geode::prelude;

ChatLayer* chatLayer = nullptr;

$execute {
    bool chatEnabled = Mod::get()->getSettingValue<bool>("chat");

    if (chatEnabled) {
        chatLayer = ChatLayer::create();
        if (chatLayer) {
            CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();
            chatLayer->setZOrder(9);
            chatLayer->setVisible(false);
            SceneManager::get()->keepAcrossScenes(chatLayer);
        }
    }
}

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        if (chatLayer && Mod::get()->getSettingValue<bool>("auto-toggle-chat")) {
            chatLayer->setVisible(true);
        }

        return true;
    }

    void onQuit() {
        if (chatLayer) {
            chatLayer->setVisible(false);
        }

        PlayLayer::onQuit();
    }
};

#if defined(GEODE_IS_WINDOWS)

#include <geode.custom-keybinds/include/Keybinds.hpp>
using namespace keybinds;

$execute {
    BindManager::get()->registerBindable({
        "chat-toggle"_spr,
        "Toggle Chat",
        "Toggles the chat's visibility in-game.",
        { Keybind::create(KEY_C, Modifier::Shift) },
        "GDStream/Chat"
    });

    new EventListener([=](InvokeBindEvent* event) {
        if (event->isDown() && chatLayer) {
            chatLayer->setVisible(!chatLayer->isVisible());
        }
        return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "chat-toggle"_spr));
}

#endif
