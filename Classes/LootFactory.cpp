//
// Created by Jarad DeLorenzo on 4/13/16.
//

#include "LootFactory.h"
#include "MoneyBagTile.h"
#include "LameSpiderSword.h"

using namespace lorafel;

LootFactory* LootFactory::_instance;

void LootFactory::init() {
    setPlayer(PlayerManager::getInstance()->getPlayer());
    m_pTileConfigs = new TileConfigs();
    m_pRandomizer = new NormalDistributionRandomizer();

    loadBasicLoot();
}

Tile* LootFactory::createTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    u_long result = m_pRandomizer->randomize(probs);
    return m_pTileConfigs->at(result)->create();
}

Tile* LootFactory::createTile(TileConfigs* pTileConfigs) {
    std::vector<int> probs;
    for (unsigned long i = 0; i < pTileConfigs->size(); ++i) {
        probs.push_back(pTileConfigs->at(i)->frequency);
    }
    u_long result = m_pRandomizer->randomize(probs);
    return pTileConfigs->at(result)->create();
}

Tile* LootFactory::createTile(Tile* pTile) {
    TileConfigs* basicLoot = getBasicLoot();
    TileConfigs* xpLoot = getXpLoot();
    TileConfigs* levelLoot = getLevelLoot();
    TileConfigs* tileLoot = pTile->getLoot();

    TileConfigs* allLoot = new TileConfigs();
    allLoot->reserve(basicLoot->size() + xpLoot->size() + levelLoot->size() + tileLoot->size());
    allLoot->insert(allLoot->end(), basicLoot->begin(), basicLoot->end());
    allLoot->insert(allLoot->end(), xpLoot->begin(), xpLoot->end());
    allLoot->insert(allLoot->end(), levelLoot->begin(), levelLoot->end());
    allLoot->insert(allLoot->end(), tileLoot->begin(), tileLoot->end());

    return createTile(allLoot);
}

void LootFactory::loadBasicLoot() {
    TileConfig* config = new TileConfig();
    config->create = std::bind([=](){ return MoneyBagTile::create();});
    config->frequency = 7;
    m_pTileConfigs->push_back(config);

    config->create = std::bind([=](){ return LameSpiderSword::create();});
    config->frequency = 7;
    m_pTileConfigs->push_back(config);

}

TileConfigs* LootFactory::getBasicLoot() {
    return m_pTileConfigs;
}

TileConfigs* LootFactory::getXpLoot() {
    return m_pTileConfigs;
}

TileConfigs* LootFactory::getLevelLoot() {
    return m_pTileConfigs;
}













