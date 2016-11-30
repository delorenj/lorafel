//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_LEVEL_TESTLEVELFOUR_H
#define LORAFEL_LEVEL_TESTLEVELFOUR_H

#include "SeededLevel.h"
#include "Tile.h"
#include "LootTile.h"
#include "NormalDistributionRandomizer.h"
#include "AvocadoTile.h"
#include "GrapeTile.h"
#include "CarrotTile.h"
#include "MeleeAttackTile.h"
#include "MoneyBagTile.h"
#include "StickMan.h"
#include "PlayerManager.h"
#include "BasicTurnManager.h"
#include "GridTransparency.h"
#include "StupidRandomizer.h"
#include "LootFactory.h"

namespace lorafel {
#define AVOCADO col->emplace_back(m_pTileConfigs->at(0)->create());
#define CARROT col->emplace_back(m_pTileConfigs->at(1)->create());
#define GRAPE col->emplace_back(m_pTileConfigs->at(2)->create());
#define MELEE_ATTACK col->emplace_back(m_pTileConfigs->at(3)->create());
#define MONEYBAG col->emplace_back(m_pTileConfigs->at(4)->create());
#define STICKMAN col->emplace_back(StickMan::create());
#define LOOT col->emplace_back(LootFactory::getInstance()->createTile());
#define HERO col->emplace_back(PlayerManager::getInstance()->getPlayer()->getTile());

    class Level__TestLevelFour : public SeededLevel {
    public:

        Level__TestLevelFour(SwappyGrid* grid) : SeededLevel(grid) {

			Tile::TileConfig* config = new Tile::TileConfig();
                config->create = std::bind([=]() { return AvocadoTile::create(); });
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                config = new Tile::TileConfig();
                config->create = std::bind([=]() { return CarrotTile::create(); });
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                config = new Tile::TileConfig();
                config->create = std::bind([=]() { return GrapeTile::create(); });
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                config = new Tile::TileConfig();
                config->create = std::bind([=]() { return MeleeAttackTile::create(); });
                config->frequency = 2;
                m_pTileConfigs->push_back(config);

                config = new Tile::TileConfig();
                config->create = std::bind([=]() { return MoneyBagTile::create(); });
                config->frequency = 1;
                m_pTileConfigs->push_back(config);

                // Col0
                auto col = new TileColumn();
                GRAPE GRAPE CARROT MELEE_ATTACK MELEE_ATTACK CARROT AVOCADO GRAPE MELEE_ATTACK
                m_initialGrid.push_back(col);

                // Col1
                col = new TileColumn();
                CARROT CARROT AVOCADO CARROT CARROT MELEE_ATTACK GRAPE CARROT AVOCADO
                m_initialGrid.push_back(col);

                // Col2
                col = new TileColumn();
                AVOCADO GRAPE MONEYBAG AVOCADO GRAPE CARROT CARROT AVOCADO CARROT
                m_initialGrid.push_back(col);

                // Col3
                col = new TileColumn();
                MONEYBAG MONEYBAG CARROT GRAPE MELEE_ATTACK CARROT GRAPE CARROT AVOCADO
                m_initialGrid.push_back(col);

                // Col4
                col = new TileColumn();
                AVOCADO GRAPE MELEE_ATTACK HERO CARROT AVOCADO GRAPE GRAPE AVOCADO
                m_initialGrid.push_back(col);

                // Col5
                col = new TileColumn();
                STICKMAN AVOCADO LOOT AVOCADO CARROT GRAPE AVOCADO GRAPE GRAPE
                m_initialGrid.push_back(col);

                // Col6
                col = new TileColumn();
                GRAPE GRAPE CARROT GRAPE GRAPE CARROT CARROT AVOCADO MONEYBAG
                m_initialGrid.push_back(col);

                // Col7
                col = new TileColumn();
                LOOT CARROT GRAPE AVOCADO CARROT GRAPE AVOCADO AVOCADO GRAPE
                m_initialGrid.push_back(col);

                // Col8
                col = new TileColumn();
                AVOCADO AVOCADO GRAPE CARROT GRAPE CARROT AVOCADO CARROT AVOCADO
                m_initialGrid.push_back(col);
        }

    };
}

#endif //LORAFEL_LEVEL_TESTLEVELFOUR_H
