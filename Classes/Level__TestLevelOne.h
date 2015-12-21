//
// Created by Jarad DeLorenzo on 12/20/15.
//

#ifndef LORAFEL_LEVEL_TESTLEVELONE_H
#define LORAFEL_LEVEL_TESTLEVELONE_H

#include "Level.h"
#include "Tile.h"

namespace lorafel {
    class Level__TestLevelOne : public Level {
        virtual Tile *getRandomTile();
    };
}

#endif //LORAFEL_LEVEL_TESTLEVELONE_H
