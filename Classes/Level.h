//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_LEVEL_H
#define LORAFEL_LEVEL_H

#include "Tile.h"
#include "IRandomizerStrategy.h"


namespace lorafel {
    typedef struct {Tile* tile; float frequency;} TileConfig;
    typedef std::list<TileConfig*> TileConfigs;

    class Level {

    public:
        Level();
        virtual ~Level();

        TileConfigs* getTileConfigs() { return tileConfigs; }


        virtual Tile* getRandomTile() = 0;

    protected:
        TileConfigs* tileConfigs;
        IRandomizerStrategy* randomizer;
    };
}

#endif //LORAFEL_LEVEL_H
