//
// Created by Jarad DeLorenzo on 4/22/16.
//

#include "ToggleActionTile.h"
#include "Globals.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"

using namespace lorafel;

bool ToggleActionTile::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }
    addEvents();
    setTag(Tag::TOGGLE_ACTION_TILE);
    return true;
}

void ToggleActionTile::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(ToggleActionTile::onTouchBegan, this);

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool ToggleActionTile::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto state = (GameState*) GameStateMachine::getInstance()->getState();
    if(state->isBusy()) {
        return false;
    }

    auto player = PlayerManager::getInstance()->getPlayer();

    cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
    cocos2d::Rect rect = this->getBoundingBox();
    m_pSwappyGrid->setCurrentTouchId(touch->_ID);

    if(rect.containsPoint(p))
    {
        toggleAction();
//        GameStateMachine::getInstance()->setState<TileTouchStartState>();
//        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
//        touchState->setTouchStartPos(p);
//        touchState->setTileStartPos(getPosition());
//        m_pSwappyGrid->clearVisitStates();
        return true; // to indicate that we have consumed it.
    }

    return false; // we did not consume this event, pass thru.
}





