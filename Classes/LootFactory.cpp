//
// Created by Jarad DeLorenzo on 4/13/16.
//

#include "LootFactory.h"
#include "MoneyBagTile.h"
#include "LameSpiderSwordTile.h"
#include "StupidRandomizer.h"

using namespace lorafel;

LootFactory* LootFactory::_instance;

void LootFactory::init() {
    setPlayer(PlayerManager::getInstance()->getPlayer());
    m_pTileConfigs = new TileConfigs();

    #ifdef DISABLE_RANDOM_SEED
        m_pRandomizer = new StupidRandomizer();
    #else
        m_pRandomizer = new NormalDistributionRandomizer();
    #endif

    loadBasicLoot();
}

Tile* LootFactory::createTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    int result = m_pRandomizer->randomize(probs);
    return m_pTileConfigs->at(result)->create();
}

Tile* LootFactory::createTile(TileConfigs* pTileConfigs) {
    std::vector<int> probs;
    for (unsigned long i = 0; i < pTileConfigs->size(); ++i) {
        probs.push_back(pTileConfigs->at(i)->frequency);
    }
    int result = m_pRandomizer->randomize(probs);
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

    auto tile = createTile(allLoot);
//    CC_SAFE_DELETE(xpLoot);
//    CC_SAFE_DELETE(levelLoot);
//    CC_SAFE_DELETE(tileLoot);
    return tile;
}

void LootFactory::loadBasicLoot() {
    TileConfig* config;

    config =new TileConfig();
    config->create = std::bind([=](){ return MoneyBagTile::create();});
    config->frequency = 0;
    m_pTileConfigs->push_back(config);

    config = new TileConfig();
    config->create = std::bind([=](){ return LameSpiderSwordTile::create();});
    config->frequency = 10;
    m_pTileConfigs->push_back(config);

}

TileConfigs* LootFactory::getBasicLoot() {
    return m_pTileConfigs;
}

TileConfigs* LootFactory::getXpLoot() {
    return new TileConfigs();
}

TileConfigs* LootFactory::getLevelLoot() {
    return new TileConfigs();
}













