//
// Created by Jarad DeLorenzo on 12/20/15.
//

#ifndef LORAFEL_LEVEL_TESTLEVELONE_H
#define LORAFEL_LEVEL_TESTLEVELONE_H

#include "SeededLevel.h"
#include "Tile.h"
#include "NormalDistributionRandomizer.h"
#include "AvocadoFactory.h"
#include "CarrotFactory.h"
#include "GrapeFactory.h"

namespace lorafel {
    class Level__TestLevelOne : public SeededLevel {
    public:
        Level__TestLevelOne(SwappyGrid *grid) : SeededLevel(grid) {
            m_pTileConfigs = new TileConfigs();
            randomizer = new NormalDistributionRandomizer();
            TileConfig *config = new TileConfig();
            config->factory = AvocadoFactory::getInstance();
            config->frequency = 5;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = CarrotFactory::getInstance();
            config->frequency = 7;
            m_pTileConfigs->push_back(config);

            config = new TileConfig();
            config->factory = GrapeFactory::getInstance();
            config->frequency = 10;
            m_pTileConfigs->push_back(config);

            // Col1
            auto col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col2
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col3
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col4
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col5
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col6
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col7
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col8
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
            m_initialGrid.push_back(col);

            // Col9
            col = new TileColumn();
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
            m_initialGrid.push_back(col);
        };
    };
}

#endif //LORAFEL_LEVEL_TESTLEVELONE_H
