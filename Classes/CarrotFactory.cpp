//
// Created by Jarad DeLorenzo on 12/22/15.
//

#include "CarrotFactory.h"
#include "CarrotTile.h"

using namespace lorafel;


Tile* CarrotFactory::createTile() {
    return CarrotTile::create();

}