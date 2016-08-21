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

/**
 * For Loot tiles, just call addToInventory()
 * on the underlying tile's item
 */
bool LootTile::addToInventory() {
    m_pLootItem->addToInventory();
    return true;
}



