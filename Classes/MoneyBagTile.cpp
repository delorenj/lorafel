//
// Created by Jarad DeLorenzo on 2/24/16.
//

#include "MoneyBagTile.h"
#include "Globals.h"
#include "GoldStatResult.h"

using namespace lorafel;

MoneyBagTile::MoneyBagTile() {
}

MoneyBagTile::~MoneyBagTile() {
}

MoneyBagTile* MoneyBagTile::create() {
    MoneyBagTile* sprite = new MoneyBagTile();

    if (sprite->initWithSpriteFrameName("money_bag_1.png"))
    {
        sprite->setTileName("MoneyBag");
        sprite->setTag(Tag::TILE);
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        sprite->addStatResult(new GoldStatResult(100));
        return sprite;
    }

    CC_SAFE_DELETE(sprite);


    return NULL;
}