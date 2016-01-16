//
// Created by Jarad DeLorenzo on 12/20/15.
//

#ifndef LORAFEL_LEVEL_TESTRANDOM_H
#define LORAFEL_LEVEL_TESTRANDOM_H

#include "Level.h"
#include "Tile.h"
#include "AvocadoFactory.h"
#include "CarrotFactory.h"
#include "GrapeFactory.h"
#include "BearFactory.h"
#include "NormalDistributionRandomizer.h"

namespace lorafel {
    class Level__TestRandom : public Level {
    public:
        Level__TestRandom(SwappyGrid* grid) : Level(grid) {
            m_pTileConfigs = new TileConfigs();
            randomizer = new NormalDistributionRandomizer();

            TileConfig* config = new TileConfig();
            config->factory = new AvocadoFactory();
            config->frequency = 5;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = new CarrotFactory();
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = new GrapeFactory();
            config->frequency = 10;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = new BearFactory();
            config->frequency = 9;
            m_pTileConfigs->push_back(config);

        };
    };
}

#endif //LORAFEL_LEVEL_TESTRANDOM_H
