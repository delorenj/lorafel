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

            m_pProjectile = Arrow::create(m_pSwappyGrid);
            addChild(m_pProjectile);
            cocos2d::Vec2 p = touch->getLocation();
            cocos2d::Vec2 mp = cocos2d::Vec2(p.x - m_pSwappyGrid->getTileSize().width / 2, p.y - m_pSwappyGrid->getTileSize().width / 2);
            m_pProjectile->setPosition(convertToNodeSpace(p));
            m_pProjectile->setRotation(getAngleToPoint(-convertToNodeSpace(mp)) + 90);
            return true;
        }

        return false;
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
    auto pos = getParent()->getPosition();
    CCLOG("%f,%f", pos.x, pos.y);
    m_pRope->setPosition(pos);
}

void Hook::hideApparatus() {
}

void Hook::onArrowTimeout(float dt) {
    auto state = GameStateMachine::getInstance()->getState();
    if(state->getName() == "HookFireStartState") {
        GameStateMachine::getInstance()->setState<IdleHookModeState>();
    }
}









