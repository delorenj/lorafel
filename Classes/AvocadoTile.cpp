//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "AvocadoTile.h"
#include "XpStatResult.h"

using namespace lorafel;

AvocadoTile* AvocadoTile::create() {
    AvocadoTile* sprite = new AvocadoTile();

    if (sprite->initWithSpriteFrameName("avocado.png"))
    {
        sprite->setTileName("Avocado");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        sprite->addStatResult(new XpStatResult(2));
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}
