//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_AVOCADOTILE_H
#define LORAFEL_AVOCADOTILE_H

#include "Tile.h"

namespace lorafel {
    class AvocadoTile : public Tile {
    public:
        AvocadoTile();
        ~AvocadoTile();

        static AvocadoTile* create();

        bool isSwappable() override;

    };
}

#endif //LORAFEL_AVOCADOTILE_H
