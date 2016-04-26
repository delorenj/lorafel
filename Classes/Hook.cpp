//
// Created by Jarad DeLorenzo on 4/26/16.
//

#include "Hook.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"

using namespace lorafel;

bool Hook::init(lorafel::Tile* pSourceTile) {
    if(!cocos2d::Node::init()) {
        return false;
    }

    m_pSourceTile = pSourceTile;
    m_pProjectile = cocos2d::Sprite::createWithSpriteFrameName("arrow.png");
//    m_pProjectile->setVisible(false);
    addChild(m_pProjectile);
    m_pSwappyGrid = m_pSourceTile->getGrid();
    m_pSwappyGrid->addChild(this);
    setPosition(PTILE_CENTER(m_pSourceTile));
    addEvents();
    return true;
}

void Hook::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->getName() != "IdleHookModeState") {
            return false;
        }
        cocos2d::Vec2 p = m_pSwappyGrid->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = m_pSourceTile->getBoundingBox();
        m_pSwappyGrid->setCurrentTouchId(touch->_ID);

        if(rect.containsPoint(p)) {
            cocos2d::Vec2 p = m_pSwappyGrid->convertToNodeSpace(touch->getLocation());
            GameStateMachine::getInstance()->enterState<HookTouchStartState>();
            auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTouchStartPos(p);
            touchState->setTileStartPos(getPosition());
            m_pSwappyGrid->clearVisitStates();
            return true;

        } else {
            return false;
        }

    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if("HookTouchStartState" == touchState->getName()) {
            /**
             * Initialize the aimer thing
             */
            auto tilePos = touchState->getTileStartPos();
            auto touchPos = touchState->getTouchStartPos();
            GameStateMachine::getInstance()->enterState<HookTouchMoveState>();
            touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTileStartPos(tilePos);
            touchState->setTouchStartPos(touchPos);
        }
        if("HookTouchMoveState" == touchState->getName()) {
            /**
             * Move aimer thing around
             */
            cocos2d::Vec2 delta = m_pSwappyGrid->convertToNodeSpace(touch->getLocation()) - touchState->getTouchStartPos();
            auto newPos = cocos2d::Vec2(touchState->getTileStartPos().x + delta.x, touchState->getTileStartPos().y + delta.y);
            m_pProjectile->setVisible(true);
            m_pProjectile->setPosition(m_pSwappyGrid->convertToNodeSpace(touch->getLocation()));
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();

        if(touchState->getName() == "HookTouchStartState") {
            /**
             * No action, just go back to idle
             */
            GameStateMachine::getInstance()->enterState<IdleHookModeState>();
            m_pProjectile->setVisible(false);
        } else if(touchState->getName() == "HookTouchMoveState") {
            /**
             * Let's fire the aimer hook thing
             */
            // For now, just go back to idle.
            GameStateMachine::getInstance()->enterState<IdleHookModeState>();
        }

        // Valid tiles are marked Tile::Color::YELLOW
        // Clear that shit out.
        m_pSwappyGrid->clearVisitStates();
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}






