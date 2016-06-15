//
// Created by Jarad DeLorenzo on 6/10/16.
//

#include "CharacterButton.h"
#include "GameStateMachine.h"
#include "InGameSettings.h"
#include "CharacterModal.h"

using namespace lorafel;

bool CharacterButton::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    initWithSpriteFrameName("character-button.png");
    addEvents();
    return true;
}

void CharacterButton::addEvents() {
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
            CharacterModal::createAndDropIn(getParent());
            return true;
        }
        return false;
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}



