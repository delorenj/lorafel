//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "CarrotTile.h"

using namespace lorafel;

CarrotTile::CarrotTile() {
}

CarrotTile::~CarrotTile() {
}

CarrotTile* CarrotTile::create() {
    CarrotTile* sprite = new CarrotTile();

    if (sprite->initWithSpriteFrameName("carrot.png"))
    {
        sprite->setSpriteName("Carrot");

        sprite->autorelease();

        sprite->initOptions();

        return sprite;
    }

    CC_SAFE_DELETE(sprite);


    return NULL;
}

void CarrotTile::initOptions() {
    // do things here like setTag(), setPosition(), any custom logic.
}
