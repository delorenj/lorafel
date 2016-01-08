//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "Tile.h"
#include "GameStateMachine.h"
#include "BasicPlayerMove.h"

using namespace lorafel;

bool Tile::init() {
    return true;
}

const std::string& Tile::getTileName() const{
    return m_tileName;
}

void Tile::setTileName(const std::string name) {
    m_tileName = name;
}
void Tile::initOptions() {
    this->setTag(1);
    this->setAnchorPoint(cocos2d::Vec2(0,0));
//    auto body = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PhysicsMaterial(1.0,0.3,1.0));
//    body->setRotationEnable(false);
//    body->setDynamic(true);
//    body->setEnabled(false);
//    body->setGravityEnable(true);
//    body->setMass(1.0);
//    this->setPhysicsBody(body);
//    this->scheduleUpdate();
}

void Tile::update(float delta) {
}

void Tile::setGrid(SwappyGrid *pGrid) {
    m_pSwappyGrid = pGrid;
}

SwappyGrid* Tile::getGrid() {
    return m_pSwappyGrid;
}

void Tile::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = this->getBoundingBox();

        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        GameState* state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->isBusy() || touch->_ID == m_pSwappyGrid->getCurrentTouchId()) {
            return;
        } else {
            m_pSwappyGrid->setCurrentTouchId(touch->_ID);
            cocos2d::Vec2 swapVec = getSwapVec(touch);
            auto playerMove = new BasicPlayerMove(m_pSwappyGrid, this, swapVec);
            if(playerMove->isValid()) {
                m_pSwappyGrid->getMoveStack()->push(playerMove);
                m_pSwappyGrid->getMoveStack()->top()->run();
            }
        }
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        // Nothing, yet.
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

cocos2d::Vec2 Tile::getSwapVec(cocos2d::Touch *pTouch) {
    cocos2d::Vec2 delta = pTouch->getDelta();
    cocos2d::Vec2 result;

    bool horizontal = std::abs(delta.x) > std::abs(delta.y);
    if (horizontal && delta.x > 0) {
        result.set(1, 0);
    } else if (horizontal && delta.x < 0) {
        result.set(-1, 0);
    } else if (!horizontal && delta.y < 0) {
        result.set(0, -1);
    } else if (!horizontal && delta.y > 0) {
        result.set(0, 1);
    } else {
        result.setZero();
    }
    return result;
}

bool Tile::isSwappable() {
    return true;
}

