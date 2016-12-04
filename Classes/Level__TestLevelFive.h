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
#include "CarrotTile.h"
#include "GrapeTile.h"
#include "AvocadoTile.h"

namespace lorafel {
    class Level__TestLevelFive : public Level {
    public:

        Level__TestLevelFive(SwappyGrid *grid) : Level() {

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
        }
    };
}

#endif //LORAFEL_LEVEL_TESTLEVELFIVE_H
