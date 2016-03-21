//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_LEVEL_TESTLEVELFOUR_H
#define LORAFEL_LEVEL_TESTLEVELFOUR_H

#include "SeededLevel.h"
#include "Tile.h"
#include "NormalDistributionRandomizer.h"
#include "AvocadoFactory.h"
#include "GrapeFactory.h"
#include "CarrotFactory.h"
#include "MeleeAttackFactory.h"
#include "MoneyBagFactory.h"
#include "StickMan.h"
#include "PlayerManager.h"
#include "BasicTurnManager.h"
#include "GridTransparency.h"

namespace lorafel {
#define AVOCADO col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
#define CARROT col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
#define GRAPE col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
#define MELEE_ATTACK col->emplace_back(m_pTileConfigs->at(3)->factory->createTile());
#define MONEYBAG col->emplace_back(m_pTileConfigs->at(4)->factory->createTile());
#define STICKMAN col->emplace_back(StickMan::create());
#define HERO col->emplace_back(PlayerManager::getInstance()->getPlayer()->getTile());

    class Level__TestLevelFour : public SeededLevel {
    public:

        Level__TestLevelFour(SwappyGrid* grid) : SeededLevel(grid) {
                m_pTurnManager = new BasicTurnManager();
                m_pTurnManager->setSwappyGrid(m_pSwappyGrid);

                m_pTileConfigs = new TileConfigs();
                randomizer = new NormalDistributionRandomizer();
                TileConfig* config = new TileConfig();
                config->factory = AvocadoFactory::getInstance();
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                config = new TileConfig();
                config->factory = CarrotFactory::getInstance();
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                config = new TileConfig();
                config->factory = GrapeFactory::getInstance();
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                config = new TileConfig();
                config->factory = MeleeAttackFactory::getInstance();
                config->frequency = 2;
                m_pTileConfigs->push_back(config);

                config = new TileConfig();
                config->factory = MoneyBagFactory::getInstance();
                config->frequency = 1;
                m_pTileConfigs->push_back(config);

                /**
                 * Insert background transparency tiles
                 */
                for(int i=0; i< SwappyGrid::NUM_COLUMNS; i++) {
                    for(int j=0; j < SwappyGrid::NUM_ROWS; j++) {
                        GridTransparency::Tile::Color color = (i+j) % 2 == 0 ? GridTransparency::Tile::Color::LIGHT : GridTransparency::Tile::Color::DARK;
                        GridTransparency::Tile::Type type;

                        if(i == 0 && j == SwappyGrid::NUM_ROWS-1) { // TopLeft
                            type = GridTransparency::Tile::Type::TOP_LEFT;
                        } else if(i == 0 && j > 0 && j < SwappyGrid::NUM_ROWS-1) {
                            type = GridTransparency::Tile::Type::LEFT;
                        } else if(i == 0 && j == 0 ) {
                            type = GridTransparency::Tile::Type::BOTTOM_LEFT;
                        } else if(i > 0 && j == 0 && i < SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::BOTTOM;
                        } else if(j == 0 && i == SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::BOTTOM_RIGHT;
                        } else if(j < SwappyGrid::NUM_ROWS-1 && j > 0 && i == SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::RIGHT;
                        } else if(j == SwappyGrid::NUM_ROWS-1 && i == SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::TOP_RIGHT;
                        } else if(i > 0 && i < SwappyGrid::NUM_COLUMNS-1 && j == SwappyGrid::NUM_ROWS-1) {
                            type = GridTransparency::Tile::Type::TOP;
                        } else {
                            type = GridTransparency::Tile::Type::CENTER;
                        }

                        m_pSwappyGrid->getGridTransparency()->insertTile(
                                m_pSwappyGrid->gridToScreen(i,j),
                                GridTransparency::Tile(color, type)
                        );
                    }
                }
                // Col0
                auto col = new TileColumn();
                CARROT GRAPE CARROT AVOCADO CARROT MELEE_ATTACK AVOCADO AVOCADO CARROT
                m_initialGrid.push_back(col);

                // Col1
                col = new TileColumn();
                GRAPE CARROT AVOCADO AVOCADO CARROT CARROT AVOCADO GRAPE GRAPE
                m_initialGrid.push_back(col);

                // Col2
                col = new TileColumn();
                AVOCADO GRAPE MONEYBAG CARROT GRAPE AVOCADO CARROT AVOCADO CARROT
                m_initialGrid.push_back(col);

                // Col3
                col = new TileColumn();
                MONEYBAG MONEYBAG CARROT GRAPE GRAPE AVOCADO AVOCADO GRAPE AVOCADO
                m_initialGrid.push_back(col);

                // Col4
                col = new TileColumn();
                AVOCADO GRAPE MELEE_ATTACK MELEE_ATTACK CARROT MELEE_ATTACK HERO MELEE_ATTACK GRAPE
                m_initialGrid.push_back(col);

                // Col5
                col = new TileColumn();
                STICKMAN AVOCADO MELEE_ATTACK GRAPE AVOCADO GRAPE AVOCADO MELEE_ATTACK GRAPE
                m_initialGrid.push_back(col);

                // Col6
                col = new TileColumn();
                MELEE_ATTACK GRAPE CARROT MELEE_ATTACK CARROT CARROT GRAPE CARROT CARROT
                m_initialGrid.push_back(col);

                // Col7
                col = new TileColumn();
                MELEE_ATTACK AVOCADO CARROT MELEE_ATTACK CARROT AVOCADO CARROT AVOCADO GRAPE
                m_initialGrid.push_back(col);

                // Col8
                col = new TileColumn();
                AVOCADO CARROT GRAPE AVOCADO GRAPE GRAPE AVOCADO GRAPE CARROT
                m_initialGrid.push_back(col);
        }

    };
}

#endif //LORAFEL_LEVEL_TESTLEVELFOUR_H
