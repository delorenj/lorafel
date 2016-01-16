//
// Created by Jarad DeLorenzo on 1/12/16.
//

#ifndef LORAFEL_LEVEL_TESTLEVELTWO_H
#define LORAFEL_LEVEL_TESTLEVELTWO_H

#include "SeededLevel.h"
#include "Tile.h"
#include "AvocadoFactory.h"
#include "CarrotFactory.h"
#include "BearFactory.h"
#include "GrapeFactory.h"
#include "NormalDistributionRandomizer.h"

namespace lorafel {
    class Level__TestLevelTwo : public SeededLevel {
    public:
        Level__TestLevelTwo(SwappyGrid *grid) : SeededLevel(grid) {
            m_pTileConfigs = new TileConfigs();
            randomizer = new NormalDistributionRandomizer();
            TileConfig* config = new TileConfig();
            config->factory = new AvocadoFactory();
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = new CarrotFactory();
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = new GrapeFactory();
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = new BearFactory();
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            // Col0
            auto col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(3)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col1
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col2
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(3)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col4
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col5
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col6
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col7
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(3)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col8
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col9
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(3)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);
        }
    };
}


#endif //LORAFEL_LEVEL_TESTLEVELTWO_H
