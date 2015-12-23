//
// Created by Jarad DeLorenzo on 12/22/15.
//

#include "AvocadoFactory.h"
#include "AvocadoTile.h"

using namespace lorafel;


Tile* AvocadoFactory::createTile() {
    return AvocadoTile::create();

}