//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_LEVEL_H
#define LORAFEL_LEVEL_H

#include "Tile.h"
#include "IRandomizerStrategy.h"
#include "TileFactory.h"
#include "SwappyGrid.h"


namespace lorafel {
    class TileFactory;
    typedef struct {TileFactory* factory; int frequency;} TileConfig;
    typedef std::vector<TileConfig*> TileConfigs;

    class Level {

    public:
        Level(SwappyGrid* grid) : m_pSwappyGrid(grid) { };

        virtual ~Level() { };

        Level(TileConfigs* configs) {
            this->m_pTileConfigs = configs;
        }

        virtual bool isCleared() const;

        TileConfigs* getTileConfigs() { return m_pTileConfigs; }
        void setTileConfigs(TileConfigs* configs) { this->m_pTileConfigs = configs; }

        virtual Tile* getRandomTile();

        virtual void load() {
            for (int i = 0; i < SwappyGrid::NUM_COLUMNS; ++i) {
                for (int j = 0; j < SwappyGrid::NUM_ROWS; ++j) {
                    m_pSwappyGrid->addRandomTileToDropQueue(i);
                }
            }
        }


    protected:
        SwappyGrid* m_pSwappyGrid;
        TileConfigs* m_pTileConfigs;
        IRandomizerStrategy* randomizer;
    };
}

#endif //LORAFEL_LEVEL_H
