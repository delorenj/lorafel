//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_LEVEL_H
#define LORAFEL_LEVEL_H

#include "IRandomizerStrategy.h"
#include "TileFactory.h"
#include "SwappyGrid.h"
#include "TurnManager.h"

namespace lorafel {
    class Tile;
    class TileFactory;
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
        virtual Tile* getRandomLoot(Tile* sourceTile = nullptr);

        virtual void load() {
            for (int i = 0; i < SwappyGrid::NUM_COLUMNS; ++i) {
                for (int j = 0; j < SwappyGrid::NUM_ROWS; ++j) {
                    m_pSwappyGrid->addRandomTileToDropQueue(i);
                }
            }
        }

        TurnManager* getTurnManager();

    protected:
        SwappyGrid* m_pSwappyGrid;
        TileConfigs* m_pTileConfigs;
        IRandomizerStrategy* randomizer;
        TurnManager* m_pTurnManager;
    };
}

#endif //LORAFEL_LEVEL_H
