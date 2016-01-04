//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "GrapeTile.h"

using namespace lorafel;

GrapeTile::GrapeTile() {
}

GrapeTile::~GrapeTile() {
}

GrapeTile* GrapeTile::create() {
    GrapeTile* sprite = new GrapeTile();

    if (sprite->initWithSpriteFrameName("grapes.png"))
    {
        sprite->setSpriteName("Grapes");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}
