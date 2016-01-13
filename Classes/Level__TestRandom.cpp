//
// Created by Jarad DeLorenzo on 12/20/15.
//

#include "Level__TestRandom.h"
#include "AvocadoFactory.h"
#include "CarrotFactory.h"
#include "GrapeFactory.h"
#include "NormalDistributionRandomizer.h"

using namespace lorafel;

Level__TestRandom::Level__TestRandom(SwappyGrid* grid) : Level(grid) {

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
}

Level__TestRandom::~Level__TestRandom() {
    while(!m_pTileConfigs->empty()) delete m_pTileConfigs->front(), m_pTileConfigs->pop_back();
}

void Level__TestRandom::load() {
    for (int i = 0; i < SwappyGrid::NUM_COLUMNS; ++i) {
        for (int j = 0; j < SwappyGrid::NUM_ROWS; ++j) {
            m_pSwappyGrid->addRandomTileToDropQueue(i);
        }
    }
}
