#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

$execute {
    new EventListener<EventFilter<ModLogoUIEvent>>(+[](ModLogoUIEvent* event) {
        if (event->getModID() == "omgrod.gdstream") {
            // Remember: no assumptions, even trivial ones!
            if (auto fart = CCSprite::create("modLogo01.png"_spr)) {
                fart->setScaleX(5);
                fart->setScaleY(3);
                // `event->getSprite()` is guaranteed to not be `nullptr` though
                event->getSprite()->addChildAtPosition(fart, Anchor::Center);
            }
        }
        // You should always propagate Geode UI events
        return ListenerResult::Propagate;
    });
}