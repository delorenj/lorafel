//
// Created by Jarad DeLorenzo on 12/20/15.
//

#include "Level__TestLevelOne.h"
#include "AvocadoTile.h"

using namespace lorafel;

Tile* Level__TestLevelOne::getRandomTile() {
    Tile* tile = AvocadoTile::create();
    return tile;
}
