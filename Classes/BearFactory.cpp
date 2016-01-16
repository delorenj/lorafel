//
// Created by Jarad DeLorenzo on 1/15/16.
//

#include "BearTile.h"
#include "BearFactory.h"

using namespace lorafel;


Tile* BearFactory::createTile() {
    return BearTile::create();

}