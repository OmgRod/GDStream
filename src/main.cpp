#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "layers/chatbox/ChatLayer.hpp"
#include <gd-addons/GDAddons.hpp>

using namespace geode::prelude;

ChatLayer* chatLayer = nullptr;

$execute {
    bool chatEnabled = Mod::get()->getSettingValue<bool>("chat");

    chatLayer = ChatLayer::create();
    if (chatLayer) {
        CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();
        chatLayer->setZOrder(9);
        if (chatEnabled) {
            chatLayer->setVisible(false);
        }
        SceneManager::get()->keepAcrossScenes(chatLayer);
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
        if (chatLayer && Mod::get()->getSettingValue<bool>("auto-toggle-chat")) {
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

    BindManager::get()->registerBindable({
        "start-stream"_spr,
        "Start Livestream",
        "Starts livestreaming.",
        { Keybind::create(KEY_R, Modifier::Shift) },
        "GDStream/Livestream"
    });

    BindManager::get()->registerBindable({
        "stop-stream"_spr,
        "Stop Livestream",
        "Stops livestreaming.",
        { Keybind::create(KEY_T, Modifier::Shift) },
        "GDStream/Livestream"
    });

    new EventListener([=](InvokeBindEvent* event) {
        if (event->isDown() && chatLayer) {
            chatLayer->setVisible(!chatLayer->isVisible());
        }
        return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "chat-toggle"_spr));
}

#endif

#if defined(GEODE_IS_ANDROID) && defined(GEODE_IS_MAC)
/*
$execute {
    // Create the CustomSwipableButton
    auto btn = gdaddons::CustomSwipableButton::create(CCSprite::create("GJ_button_01.png"));

    // Add the button to the current scene
    auto scene = CCDirector::sharedDirector()->getRunningScene();
    scene->addChild(btn);

    // Keep the button across scenes
    SceneManager::get()->keepAcrossScenes(btn);
}
*/
#endif
