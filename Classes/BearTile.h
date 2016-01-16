//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_BEARTILE_H
#define LORAFEL_BEARTILE_H

#include "Tile.h"

namespace lorafel {
    class BearTile : public Tile {
    public:
        BearTile();
        ~BearTile();

        static BearTile* create();
    };
}
#endif //LORAFEL_BEARTILE_H
