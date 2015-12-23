//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "Tile.h"

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
    auto body = cocos2d::PhysicsBody::createBox(this->getContentSize());
    body->setRotationEnable(false);
    this->setPhysicsBody(body);
}
