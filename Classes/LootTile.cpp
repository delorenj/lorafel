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
    
    setTag(Tag::LOOT);
    return true;
}

