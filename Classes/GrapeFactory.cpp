//
// Created by Jarad DeLorenzo on 12/22/15.
//

#include "GrapeFactory.h"
#include "GrapeTile.h"

using namespace lorafel;


Tile* GrapeFactory::createTile() {
    return GrapeTile::create();

}