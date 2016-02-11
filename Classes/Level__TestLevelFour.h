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
#include "BearFactory.h"
#include "StickMan.h"
#include "PlayerManager.h"
#include "BasicTurnManager.h"

namespace lorafel {
#define AVOCADO col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
#define CARROT col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
#define GRAPE col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
#define BEAR col->emplace_back(m_pTileConfigs->at(3)->factory->createTile());
#define STICKMAN col->emplace_back(StickMan::create());
#define HERO col->emplace_back(PlayerManager::getInstance()->getPlayer()->getTile());

    class Level__TestLevelFour : public SeededLevel {
    public:
        virtual ~Level__TestLevelFour() {
            CC_SAFE_DELETE(m_pTurnManager);
        }

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
                config->factory = BearFactory::getInstance();
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                // Col0
                auto col = new TileColumn();
                CARROT GRAPE BEAR AVOCADO CARROT BEAR CARROT AVOCADO GRAPE
                m_initialGrid.push_back(col);

                // Col1
                col = new TileColumn();
                GRAPE AVOCADO CARROT GRAPE AVOCADO CARROT AVOCADO BEAR CARROT
                m_initialGrid.push_back(col);

                // Col2
                col = new TileColumn();
                AVOCADO CARROT AVOCADO BEAR BEAR GRAPE GRAPE AVOCADO BEAR
                m_initialGrid.push_back(col);

                // Col4
                col = new TileColumn();
                CARROT CARROT GRAPE BEAR GRAPE AVOCADO AVOCADO STICKMAN CARROT
                m_initialGrid.push_back(col);

                // Col5
                col = new TileColumn();
                AVOCADO AVOCADO CARROT CARROT AVOCADO BEAR AVOCADO AVOCADO GRAPE
                m_initialGrid.push_back(col);

                // Col6
                col = new TileColumn();
                CARROT GRAPE CARROT AVOCADO BEAR AVOCADO STICKMAN GRAPE BEAR
                m_initialGrid.push_back(col);

                // Col7
                col = new TileColumn();
                AVOCADO HERO CARROT GRAPE BEAR BEAR AVOCADO BEAR GRAPE
                m_initialGrid.push_back(col);

                // Col8
                col = new TileColumn();
                GRAPE GRAPE BEAR CARROT GRAPE CARROT CARROT GRAPE AVOCADO
                m_initialGrid.push_back(col);

                // Col9
                col = new TileColumn();
                CARROT BEAR CARROT GRAPE AVOCADO GRAPE CARROT GRAPE GRAPE
                m_initialGrid.push_back(col);
        }

    };
}

#endif //LORAFEL_LEVEL_TESTLEVELFOUR_H
