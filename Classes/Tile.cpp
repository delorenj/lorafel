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
}

