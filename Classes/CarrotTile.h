//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_CARROTTILE_H
#define LORAFEL_CARROTTILE_H

#include "Tile.h"

namespace lorafel {
    class CarrotTile : public Tile {
    public:
        CarrotTile();
        ~CarrotTile();

        static CarrotTile* create();
        void initOptions();

    };
}

#endif //LORAFEL_CARROTTILE_H
