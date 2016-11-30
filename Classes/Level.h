//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_LEVEL_H
#define LORAFEL_LEVEL_H

#include "IRandomizerStrategy.h"
#include "SwappyGrid.h"
#include "TurnManager.h"
#include "Tile.h"

#ifndef DISABLE_RANDOM_SEED
#include "NormalDistributionRandomizer.h"
#endif

#include "BasicTurnManager.h"
#include "HeroTile.h"
#include "PlayerManager.h"

namespace lorafel {
    class Level {

    public:
        Level(SwappyGrid* grid) : m_pSwappyGrid(grid) {
            m_pTurnManager = new BasicTurnManager();
            m_pTurnManager->setSwappyGrid(m_pSwappyGrid);

            m_pTileConfigs = new Tile::TileConfigs();
            #ifdef DISABLE_RANDOM_SEED
                        randomizer = new StupidRandomizer();
            #else
                        randomizer = new NormalDistributionRandomizer();
            #endif

            /**
             * Insert background transparency tiles
             */
            for (int i = 0; i < SwappyGrid::NUM_COLUMNS; i++) {
                for (int j = 0; j < SwappyGrid::NUM_ROWS; j++) {
                    GridTransparency::Tile::Color color = (i + j) % 2 == 0 ? GridTransparency::Tile::Color::LIGHT : GridTransparency::Tile::Color::DARK;
                    GridTransparency::Tile::Type type;

                    if (i == 0 && j == SwappyGrid::NUM_ROWS - 1) { // TopLeft
                        type = GridTransparency::Tile::Type::TOP_LEFT;
                    } else if (i == 0 && j > 0 && j < SwappyGrid::NUM_ROWS - 1) {
                        type = GridTransparency::Tile::Type::LEFT;
                    } else if (i == 0 && j == 0) {
                        type = GridTransparency::Tile::Type::BOTTOM_LEFT;
                    } else if (i > 0 && j == 0 && i < SwappyGrid::NUM_COLUMNS - 1) {
                        type = GridTransparency::Tile::Type::BOTTOM;
                    } else if (j == 0 && i == SwappyGrid::NUM_COLUMNS - 1) {
                        type = GridTransparency::Tile::Type::BOTTOM_RIGHT;
                    } else if (j < SwappyGrid::NUM_ROWS - 1 && j > 0 && i == SwappyGrid::NUM_COLUMNS - 1) {
                        type = GridTransparency::Tile::Type::RIGHT;
                    } else if (j == SwappyGrid::NUM_ROWS - 1 && i == SwappyGrid::NUM_COLUMNS - 1) {
                        type = GridTransparency::Tile::Type::TOP_RIGHT;
                    } else if (i > 0 && i < SwappyGrid::NUM_COLUMNS - 1 && j == SwappyGrid::NUM_ROWS - 1) {
                        type = GridTransparency::Tile::Type::TOP;
                    } else {
                        type = GridTransparency::Tile::Type::CENTER;
                    }

                    m_pSwappyGrid->getGridTransparency()->insertTile(
                            m_pSwappyGrid->gridToScreen(i, j),
                            GridTransparency::Tile(color, type)
                    );
                }
            }
        };

        virtual ~Level() { };

        Level(Tile::TileConfigs* configs) {
            this->m_pTileConfigs = configs;
        }

        virtual bool isCleared() const;

        Tile::TileConfigs* getTileConfigs() { return m_pTileConfigs; }
        void setTileConfigs(Tile::TileConfigs* configs) { this->m_pTileConfigs = configs; }

        virtual Tile* getRandomTile();
        virtual Tile* getRandomLoot(Tile* sourceTile = nullptr);

        Tile* createTileFromGridPos(int x, int y);

        virtual void load() {
            for (int i = 0; i < SwappyGrid::NUM_COLUMNS; ++i) {
                for (int j = 0; j < SwappyGrid::NUM_ROWS; ++j) {
                    if(auto tile = createTileFromGridPos(i, j)) {
                        m_pSwappyGrid->addTileToDropQueue(i, tile);
                    } else {
                        m_pSwappyGrid->addRandomTileToDropQueue(i);
                    }
                }
            }
        }

        TurnManager* getTurnManager();

    protected:
        SwappyGrid* m_pSwappyGrid;
        Tile::TileConfigs* m_pTileConfigs;
        IRandomizerStrategy* randomizer;
        TurnManager* m_pTurnManager;
        std::map<std::pair<int, int>, cocos2d::ValueMap > m_staticTiles;
    };
}

#endif //LORAFEL_LEVEL_H
