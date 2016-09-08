//
// Created by Jarad DeLorenzo on 6/10/16.
//

#include "InGameModalNavButton.h"
#include "GameStateMachine.h"
#include "InGameSettings.h"
#include "InGameModal.h"

using namespace lorafel;

bool InGameModalNavButton::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    initWithSpriteFrameName("character-button.png");
    addEvents();
    return true;
}

void InGameModalNavButton::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if (state->isBusy()) {
            return false;
        }

        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = this->getBoundingBox();

        if (rect.containsPoint(p)) {
            CCLOG("InGameModalNavButton::onTouchBegan()");
            InGameModal::createAndDropIn(cocos2d::Director::getInstance()->getRunningScene());
            return true;
        }
        return false;
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}



