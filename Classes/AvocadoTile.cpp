//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "AvocadoTile.h"

using namespace lorafel;

AvocadoTile::AvocadoTile() {
}

AvocadoTile::~AvocadoTile() {
}

AvocadoTile* AvocadoTile::create() {
    AvocadoTile* sprite = new AvocadoTile();

    if (sprite->initWithSpriteFrameName("avocado.png"))
    {
        sprite->setSpriteName("Avocado");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();

        return sprite;
    }

    CC_SAFE_DELETE(sprite);


    return NULL;
}
