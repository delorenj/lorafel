//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_GRAPEFACTORY_H
#define LORAFEL_GRAPEFACTORY_H

#include "TileFactory.h"

namespace lorafel {
    class GrapeFactory : public TileFactory {

    public:
        virtual Tile *createTile();
    };
}

#endif //LORAFEL_GRAPEFACTORY_H
