#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "layers/chatbox/ChatLayer.hpp"

using namespace geode::prelude;

ChatLayer* chatLayer = nullptr; // Initialize to null

$execute {
    bool chatEnabled = Mod::get()->getSettingValue<bool>("chat");

    if (chatEnabled) {
        chatLayer = ChatLayer::create(); // Create ChatLayer instance
        if (chatLayer) {
            CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();
            chatLayer->setZOrder(9);
            chatLayer->setVisible(false); // Initially hidden
            SceneManager::get()->keepAcrossScenes(chatLayer); // Persist across scenes
        }
    }
}

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        if (chatLayer) {
            chatLayer->setVisible(true); // Show ChatLayer when entering PlayLayer
        }

        return true;
    }

    void onQuit() {
        if (chatLayer) {
            chatLayer->setVisible(false); // Hide ChatLayer when quitting PlayLayer
        }

        PlayLayer::onQuit();
    }
};

#if defined(GEODE_IS_WINDOWS)

#include <geode.custom-keybinds/include/Keybinds.hpp>
using namespace keybinds;

$execute {
    // Register a bindable key for toggling the chat
    BindManager::get()->registerBindable({
        "chat-toggle"_spr,
        "Toggle Chat",
        "Toggles the chat's visibility in-game.",
        { Keybind::create(KEY_C, Modifier::Shift) }, // Default key: 'C'
        "GDStream/Chat"
    });

    // Add a listener for the keybind
    new EventListener([=](InvokeBindEvent* event) {
        if (event->isDown() && chatLayer) {
            chatLayer->setVisible(!chatLayer->isVisible()); // Toggle visibility
        }
        return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "chat-toggle"_spr));
}

#endif
