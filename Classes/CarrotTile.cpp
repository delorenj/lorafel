//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "CarrotTile.h"
#include "XpStatResult.h"

using namespace lorafel;

CarrotTile::CarrotTile() {
}

CarrotTile::~CarrotTile() {
}

CarrotTile* CarrotTile::create() {
    CarrotTile* sprite = new CarrotTile();

    if (sprite->initWithSpriteFrameName("carrot.png"))
    {
        sprite->setTileName("Carrot");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        sprite->addStatResult(new XpStatResult(2));
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}
