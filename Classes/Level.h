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

    typedef struct {TileFactory* factory; int frequency;} TileConfig;
    typedef std::vector<TileConfig*> TileConfigs;

    class Level {

    public:
        Level();
        Level(TileConfigs* configs) {
            this->m_pTileConfigs = configs;
        }

        virtual ~Level();

        TileConfigs* getTileConfigs() { return m_pTileConfigs; }
        void setTileConfigs(TileConfigs* configs) { this->m_pTileConfigs = configs; }

        virtual Tile* getRandomTile();

    protected:
        TileConfigs* m_pTileConfigs;
        IRandomizerStrategy* randomizer;
    };
}

#endif //LORAFEL_LEVEL_H
