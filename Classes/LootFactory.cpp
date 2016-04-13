//
// Created by Jarad DeLorenzo on 4/13/16.
//

#include "LootFactory.h"
#include "MoneyBagTile.h"
#include "TileFactory.h"

using namespace lorafel;

TileFactory* LootFactory::_instance;

void LootFactory::init() {
    setPlayer(PlayerManager::getInstance()->getPlayer());
    m_pTileConfigs = new TileConfigs();
    m_pRandomizer = new NormalDistributionRandomizer();
    TileConfig* config = new TileConfig();
    config->create = std::bind([=](){ return MoneyBagTile::create();});
    config->frequency = 7;
    m_pTileConfigs->push_back(config);
}

Tile* LootFactory::createTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    int result = m_pRandomizer->randomize(probs);
    return m_pTileConfigs->at(result)->create();
}



