//
// Created by Jarad M DeLorenzo on 11/21/16.
//

#ifndef LORAFEL_LEVEL_TESTLEVELFIVE_H
#define LORAFEL_LEVEL_TESTLEVELFIVE_H

#include "cocos2d.h"
#include "LootFactory.h"
#include "StupidRandomizer.h"
#include "BasicTurnManager.h"
#include "Tile.h"
#include "MeleeAttackTile.h"
#include "MoneyBagTile.h"
#include "DeathBearTile.h"

namespace lorafel {
    class Level__TestLevelFive : public Level {
    public:

        Level__TestLevelFive(SwappyGrid *grid) : Level(grid) {
            m_pTurnManager = new BasicTurnManager();
            m_pTurnManager->setSwappyGrid(m_pSwappyGrid);

            m_pTileConfigs = new Tile::TileConfigs();
#ifdef DISABLE_RANDOM_SEED
            randomizer = new StupidRandomizer();
#else
            randomizer = new NormalDistributionRandomizer();
#endif

            Tile::TileConfig *config = new Tile::TileConfig();

            config->create = std::bind([=]() {
                return AvocadoTile::create();
            });
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new Tile::TileConfig();
            config->create = std::bind([=]() {
                return CarrotTile::create();
            });
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new Tile::TileConfig();
            config->create = std::bind([=]() {
                return GrapeTile::create();
            });
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new Tile::TileConfig();
            config->create = std::bind([=]() {
                return MeleeAttackTile::create();
            });
            config->frequency = 2;
            m_pTileConfigs->push_back(config);

            config = new Tile::TileConfig();
            config->create = std::bind([=]() {
                return MoneyBagTile::create();
            });
            config->frequency = 1;
            m_pTileConfigs->push_back(config);

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
        }
    };
}

#endif //LORAFEL_LEVEL_TESTLEVELFIVE_H
