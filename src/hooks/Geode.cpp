#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

$execute {
    new EventListener<EventFilter<ModLogoUIEvent>>(+[](ModLogoUIEvent* event) {
        if (event->getModID() == "omgrod.gdstream") {
            // Create the new sprite
            if (auto fart = CCSprite::create("modLogo01.png"_spr)) {
                fart->setScale(0.595f);

                // Add the new sprite to the center of the original sprite
                event->getSprite()->addChildAtPosition(fart, Anchor::Center);

                // Find and remove a specific child if it exists
                if (auto child = event->getSprite()->getChildByID("sprite")) {
                    child->setVisible(false);
                    child->setID("sprite-old");
                }

                fart->setID("sprite");
            }
        }
        // Always propagate Geode UI events
        return ListenerResult::Propagate;
    });
}
