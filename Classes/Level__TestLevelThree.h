#ifndef __LEVELTESTLEVELTHREE__
#define __LEVELTESTLEVELTHREE__

#include "SeededLevel.h"
#include "Tile.h"
#include "NormalDistributionRandomizer.h"
#include "AvocadoFactory.h"
#include "GrapeFactory.h"
#include "CarrotFactory.h"
#include "BearFactory.h"

namespace lorafel {
#define AVOCADO col->emplace_back(m_pTileConfigs->at(0)->factory->createTile());
#define CARROT col->emplace_back(m_pTileConfigs->at(1)->factory->createTile());
#define GRAPE col->emplace_back(m_pTileConfigs->at(2)->factory->createTile());
#define BEAR col->emplace_back(m_pTileConfigs->at(3)->factory->createTile());

    class Level__TestLevelThree : public SeededLevel {
    public:
    Level__TestLevelThree(SwappyGrid* grid) : SeededLevel(grid) {
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
            CARROT CARROT GRAPE BEAR GRAPE AVOCADO AVOCADO BEAR CARROT
            m_initialGrid.push_back(col);

            // Col5
            col = new TileColumn();
            AVOCADO AVOCADO CARROT CARROT AVOCADO BEAR AVOCADO AVOCADO GRAPE
            m_initialGrid.push_back(col);

            // Col6
            col = new TileColumn();
            CARROT GRAPE CARROT AVOCADO BEAR AVOCADO BEAR GRAPE BEAR
            m_initialGrid.push_back(col);

            // Col7
            col = new TileColumn();
            AVOCADO CARROT AVOCADO GRAPE BEAR BEAR AVOCADO BEAR GRAPE
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

#endif //__LEVELTESTLEVELTHREE__
