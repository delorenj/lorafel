//
// Created by Jarad DeLorenzo on 1/12/16.
//

#ifndef LORAFEL_LEVEL_TESTLEVELTWO_H
#define LORAFEL_LEVEL_TESTLEVELTWO_H

#include "Level.h"
#include "Tile.h"

namespace lorafel {
    class Level__TestLevelTwo : public Level {
    public:
        Level__TestLevelTwo(SwappyGrid* grid);
        virtual ~Level__TestLevelTwo();

        void load() override;
    protected:
        TileGrid m_initialGrid;
    };
}


#endif //LORAFEL_LEVEL_TESTLEVELTWO_H
