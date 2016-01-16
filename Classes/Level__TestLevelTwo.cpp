//
// Created by Jarad DeLorenzo on 0/01/06.
//

#include "Level__TestLevelTwo.h"
#include "AvocadoFactory.h"
#include "CarrotFactory.h"
#include "GrapeFactory.h"
#include "NormalDistributionRandomizer.h"
#include "BearFactory.h"

using namespace lorafel;

Level__TestLevelTwo::Level__TestLevelTwo(SwappyGrid* grid) : Level(grid) {

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

Level__TestLevelTwo::~Level__TestLevelTwo() {
    while(!m_pTileConfigs->empty()) delete m_pTileConfigs->front(), m_pTileConfigs->pop_back();
}

void Level__TestLevelTwo::load() {
    for (int i = 0; i < SwappyGrid::NUM_COLUMNS; ++i) {
        for (int j = 0; j < SwappyGrid::NUM_ROWS; ++j) {
            m_pSwappyGrid->addTileToDropQueue(i, m_initialGrid.at(i)->at(j));
        }
    }
}
