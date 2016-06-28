//
// Created by Jarad DeLorenzo on 4/14/16.
//

#include "LootTile.h"
#include "Globals.h"

using namespace lorafel;

bool LootTile::init() {
    if(!Tile::init()) {
        return false;
    }

    setGlobalZOrder(1);
    setPositionZ(1.0f);
    setLocalZOrder(1);
    setOrderOfArrival(1);
    setTag(Tag::LOOT);
    return true;
}

