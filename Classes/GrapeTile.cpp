//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "GrapeTile.h"
#include "XpStatResult.h"
#include "Globals.h"

using namespace lorafel;

GrapeTile::GrapeTile() {
}

GrapeTile::~GrapeTile() {
}

GrapeTile* GrapeTile::create() {
    GrapeTile* sprite = new GrapeTile();

    if (sprite->initWithSpriteFrameName("grapes.png"))
    {
        sprite->setTileName("Grapes");
        sprite->setTag(Tag::TILE);
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        sprite->addStatResult(new XpStatResult(2));
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}
