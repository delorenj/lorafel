//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_CARROTFACTORY_H
#define LORAFEL_CARROTFACTORY_H

#include "TileFactory.h"

namespace lorafel {
    class CarrotFactory : public TileFactory {

    public:
        virtual Tile *createTile();
    };
}
#endif //LORAFEL_CARROTFACTORY_H
