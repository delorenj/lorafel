//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "Tile.h"
#include "GameStateMachine.h"

using namespace lorafel;

bool Tile::init() {
    return true;
}

std::string Tile::getSpriteName() {
    return spriteName;
}

void Tile::setSpriteName(std::string name) {
    spriteName = name;
}
void Tile::initOptions() {
    this->setTag(1);
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    auto body = cocos2d::PhysicsBody::createBox(this->getContentSize(), cocos2d::PhysicsMaterial(1.0,0.3,1.0));
    body->setRotationEnable(false);
    body->setDynamic(true);
    body->setEnabled(false);
    body->setGravityEnable(true);
    body->setMass(1.0);
    this->setPhysicsBody(body);
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
        if(state->isBusy()) {
            return;
        }

        cocos2d::Vec2 swapVec = getSwapVec(touch);
        m_pSwappyGrid->swapTiles(this, swapVec);
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {

    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

cocos2d::Vec2 Tile::getSwapVec(cocos2d::Touch *pTouch) {
    return cocos2d::Vec2(0,1);
}
