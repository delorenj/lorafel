//
// Created by Jarad DeLorenzo on 12/20/15.
//

#include "Level__TestLevelOne.h"
#include "AvocadoTile.h"

using namespace lorafel;

Tile* Level__TestLevelOne::getRandomTile() {
    Tile* tile = AvocadoTile::create();
    tile->setTag(1);
    auto body = cocos2d::PhysicsBody::createCircle(tile->getContentSize().width / 2);

//    auto body = cocos2d::PhysicsBody::createEdgeBox(tile->getContentSize());
    tile->setPhysicsBody(body);
    return tile;
}
