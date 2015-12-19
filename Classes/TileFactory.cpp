//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "TileFactory.h"
#include "AvocadoTile.h"

using namespace lorafel;

TileFactory* TileFactory::_instance;

Tile* TileFactory::getTile(Level* pLevel) {

    return AvocadoTile::create();
}
