//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_BEARFACTORY_H
#define LORAFEL_BEARFACTORY_H

#include "TileFactory.h"

using namespace lorafel;

class BearFactory : public TileFactory{

public:
    virtual lorafel::Tile* createTile();

};


#endif //LORAFEL_BEARFACTORY_H
