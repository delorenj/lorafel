//
// Created by Jarad DeLorenzo on 12/20/15.
//

#ifndef LORAFEL_LEVEL_TESTRANDOM_H
#define LORAFEL_LEVEL_TESTRANDOM_H

#include "Level.h"
#include "Tile.h"
#include "AvocadoFactory.h"

namespace lorafel {
    class Level__TestRandom : public Level {
    public:
        Level__TestRandom(SwappyGrid* grid);
        virtual ~Level__TestRandom();

        void load() override;
    protected:
        TileGrid m_initialGrid;
    };
}

#endif //LORAFEL_LEVEL_TESTRANDOM_H
