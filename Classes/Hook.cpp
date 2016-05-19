//
// Created by Jarad DeLorenzo on 4/26/16.
//

#include "Hook.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"
#include "Globals.h"

using namespace lorafel;

/**
 * Heierarchy
 *
 * swappyGrid -> sourceTile -> this -> clippingMask -> trajectoryLines
 * swappyGrid -> sourceTile -> this -> projectile
 * swappyGrid -> sourceTile -> this -> debug
 *
 */
bool Hook::init(lorafel::Tile* pSourceTile) {
    if(!cocos2d::Node::init()) {
        return false;
    }
    m_pSourceTile = pSourceTile;
    m_pSwappyGrid = m_pSourceTile->getGrid();
    m_pSourceTile->addChild(this);
    m_pDebug = cocos2d::DrawNode::create();
    addChild(m_pDebug);
    addEvents();
    return true;
}

//void Hook::addEvents() {
//    auto listener = cocos2d::EventListenerTouchOneByOne::create();
//    listener->setSwallowTouches(true);
//
//    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
//        auto state = (GameState*) GameStateMachine::getInstance()->getState();
//        if(state->getName() != "IdleHookModeState") {
//            return false;
//        }
//        cocos2d::Vec2 p = m_pSwappyGrid->convertToNodeSpace(touch->getLocation());
//        cocos2d::Rect rect = m_pSourceTile->getBoundingBox();
//        m_pSwappyGrid->setCurrentTouchId(touch->_ID);
//
//        if(rect.containsPoint(p)) {
//            cocos2d::Vec2 p = m_pSwappyGrid->convertToNodeSpace(touch->getLocation());
//            GameStateMachine::getInstance()->enterState<HookTouchStartState>();
//            auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
//            touchState->setTouchStartPos(p);
//            touchState->setTileStartPos(getPosition());
//            m_pSwappyGrid->clearVisitStates();
//            return true;
//
//        } else {
//            return false;
//        }
//
//    };
//
//    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
//        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
//        if("HookTouchStartState" == touchState->getName()) {
//            /**
//             * Initialize the aimer thing
//             */
//            auto tilePos = touchState->getTileStartPos();
//            auto touchPos = touchState->getTouchStartPos();
//            GameStateMachine::getInstance()->enterState<HookTouchMoveState>();
//            touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
//            touchState->setTileStartPos(tilePos);
//            touchState->setTouchStartPos(touchPos);
//            return true;
//        }
//        if("HookTouchMoveState" == touchState->getName()) {
//            /**
//             * Move aimer thing around
//             */
//            m_pProjectile->setVisible(true);
//
//            /**
//             * Convert the touch coordinates to the Hero tile's
//             * coordinate system and then set the projectile's
//             * position to the touch pos
//             */
//            m_pProjectile->setPosition(m_pSourceTile->convertToNodeSpace(touch->getLocation()));
//            auto pos = m_pProjectile->getPosition();
//
//            /**
//             * Set the arrow's rotation in terms of position that
//             * was set in Hero tile's coordinate space
//             */
//            m_pProjectile->setRotation(getAngleToPoint(
//                    cocos2d::Vec2(
//                            pos.x-(
//                                    m_pSwappyGrid->getTileSize().width*m_pSwappyGrid->getTileScaleFactor()/2),
//                            pos.y-(
//                                    m_pSwappyGrid->getTileSize().height*m_pSwappyGrid->getTileScaleFactor()/2)
//                    )
//            ) - 90);
//
//            /**
//             * Show the bow & arrow particle lines
//             */
//            showApparatus();
//        }
//    };
//
//    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
//        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
//
//        if(touchState->getName() == "HookTouchStartState") {
//            /**
//             * No action, just go back to idle
//             */
//            GameStateMachine::getInstance()->enterState<IdleHookModeState>();
//            m_pProjectile->setVisible(false);
//        } else if(touchState->getName() == "HookTouchMoveState") {
//            /**
//             * Let's fire the aimer hook thing
//             */
//            // For now, just go back to idle.
//            GameStateMachine::getInstance()->enterState<IdleHookModeState>();
//            m_pProjectile->setVisible(false);
//        }
//
//        m_pSwappyGrid->clearVisitStates();
//        hideApparatus();
//    };
//
//    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
//}

void Hook::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        m_pProjectile = Arrow::create(m_pSwappyGrid);
        addChild(m_pProjectile);
        cocos2d::Vec2 p = touch->getLocation();
        cocos2d::Vec2 mp = cocos2d::Vec2(p.x - m_pSwappyGrid->getTileSize().width/2, p.y - m_pSwappyGrid->getTileSize().width/2);
        m_pProjectile->setPosition(convertToNodeSpace(p));
        m_pProjectile->setRotation(getAngleToPoint(-convertToNodeSpace(mp))+90);
        showApparatus();
        return true;
    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto p = touch->getLocation();
        auto mp = cocos2d::Vec2(p.x - m_pSwappyGrid->getTileSize().width/2, p.y - m_pSwappyGrid->getTileSize().width/2);
        auto ms = cocos2d::Vec2(m_pSwappyGrid->getTileSize().width/2, m_pSwappyGrid->getTileSize().width/2);
        auto maxDist = 200.0f;
        auto dist = convertToNodeSpace(p).getDistance(ms);
        auto angle = getAngleToPoint(-convertToNodeSpace(mp));

        if(dist >= maxDist) {

            m_pProjectile->setPosition(
                    cocos2d::Vec2(
                            ms.x-7 - maxDist*sinf(CC_DEGREES_TO_RADIANS(angle+90)),
                            ms.y-7 - maxDist*cosf(CC_DEGREES_TO_RADIANS(angle+90))
                    )
            );
        } else {
            m_pProjectile->setPosition(convertToNodeSpace(p));
        }

        m_pProjectile->setRotation(angle+90);
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        m_pProjectile->fire();
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hook::showApparatus() {
    m_pRope = Rope::create(m_pSwappyGrid, 1);
    addChild(m_pRope);
}

void Hook::hideApparatus() {
}










