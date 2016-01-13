//
// Created by Jarad DeLorenzo on 12/20/15.
//

#ifndef LORAFEL_LEVEL_TESTLEVELONE_H
#define LORAFEL_LEVEL_TESTLEVELONE_H

#include "Level.h"
#include "Tile.h"
#include "AvocadoFactory.h"

namespace lorafel {
    class Level__TestLevelOne : public Level {
    public:
        Level__TestLevelOne(SwappyGrid* grid);
        virtual ~Level__TestLevelOne();

        void load() override;
    protected:
        TileGrid m_initialGrid;
    };
}

#endif //LORAFEL_LEVEL_TESTLEVELONE_H
