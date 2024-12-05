#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include "StreamLayer.hpp"

using namespace geode::prelude;

bool StreamLayer::init() {
    if (!CCLayer::init()) return false;

    // code here

    return true;
}

StreamLayer* StreamLayer::create() {
    StreamLayer* ret = new StreamLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

CCScene* StreamLayer::scene() {
    auto scene = CCScene::create();
    scene->addChild(StreamLayer::create());
    return scene;
}
