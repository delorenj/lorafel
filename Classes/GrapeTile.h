//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_GRAPETILE_H
#define LORAFEL_GRAPETILE_H

#include "Tile.h"

namespace lorafel {
    class GrapeTile : public Tile {
    public:
        GrapeTile();
        ~GrapeTile();

        static GrapeTile* create();

    };
}

#endif //LORAFEL_GRAPETILE_H
