//
// Created by Jarad DeLorenzo on 1/15/16.
//

#include "BearTile.h"
#include "XpStatResult.h"

using namespace lorafel;

BearTile::BearTile() {
}

BearTile::~BearTile() {
}

BearTile* BearTile::create() {
    BearTile* sprite = new BearTile();

    if (sprite->initWithSpriteFrameName("bear.png"))
    {
        sprite->setTileName("Bear");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        sprite->addStatResult(new XpStatResult(4));
        return sprite;
    }

    CC_SAFE_DELETE(sprite);


    return NULL;
}