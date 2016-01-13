//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_LEVEL_H
#define LORAFEL_LEVEL_H

#include "Tile.h"
#include "IRandomizerStrategy.h"
#include "TileFactory.h"


namespace lorafel {
    class TileFactory;
    class SwappyGrid;
    typedef struct {TileFactory* factory; int frequency;} TileConfig;
    typedef std::vector<TileConfig*> TileConfigs;

    class Level {

    public:
        Level(SwappyGrid* grid) : m_pSwappyGrid(grid) { };

        virtual ~Level() { };

        Level(TileConfigs* configs) {
            this->m_pTileConfigs = configs;
        }

        TileConfigs* getTileConfigs() { return m_pTileConfigs; }
        void setTileConfigs(TileConfigs* configs) { this->m_pTileConfigs = configs; }

        virtual Tile* getRandomTile();
        virtual void load() { };

    protected:
        SwappyGrid* m_pSwappyGrid;
        TileConfigs* m_pTileConfigs;
        IRandomizerStrategy* randomizer;
    };
}

#endif //LORAFEL_LEVEL_H
