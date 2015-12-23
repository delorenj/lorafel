//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_AVOCADOFACTORY_H
#define LORAFEL_AVOCADOFACTORY_H

#include "TileFactory.h"

using namespace lorafel;

class AvocadoFactory : public TileFactory {

public:
    virtual Tile* createTile();
};


#endif //LORAFEL_AVOCADOFACTORY_H
