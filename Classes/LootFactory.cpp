//
// Created by Jarad DeLorenzo on 4/13/16.
//

#include "Globals.h"
#include "LootFactory.h"
#include "LootTile.h"

using namespace lorafel;

LootFactory* LootFactory::_instance;

void LootFactory::init() {
    setPlayer(PlayerManager::getInstance()->getPlayer());
    m_pTileConfigs = new lorafel::Tile::TileConfigs();

    #ifdef DISABLE_RANDOM_SEED
        m_pRandomizer = new StupidRandomizer();
    #else
        m_pRandomizer = new NormalDistributionRandomizer();
    #endif

    loadBasicLoot();
}

lorafel::Tile* LootFactory::createTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    int result = m_pRandomizer->randomize(probs);
    return m_pTileConfigs->at(result)->create();
}

lorafel::Tile* LootFactory::createTile(lorafel::Tile::TileConfigs* pTileConfigs) {
    std::vector<int> probs;
    for (unsigned long i = 0; i < pTileConfigs->size(); ++i) {
        probs.push_back(pTileConfigs->at(i)->frequency);
    }
    int result = m_pRandomizer->randomize(probs);
    return pTileConfigs->at(result)->create();
}

lorafel::Tile* LootFactory::createTile(lorafel::Tile* pTile) {
    lorafel::Tile::TileConfigs* basicLoot = getBasicLoot();
    lorafel::Tile::TileConfigs* xpLoot = getXpLoot();
    lorafel::Tile::TileConfigs* levelLoot = getLevelLoot();
    lorafel::Tile::TileConfigs* tileLoot = pTile->getLoot();

    lorafel::Tile::TileConfigs* allLoot = new lorafel::Tile::TileConfigs();
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
    lorafel::Tile::TileConfig* config;

//    config =new lorafel::Tile::TileConfig();
//    config->create = std::bind([=](){ return MoneyBaglorafel::Tile::create();});
//    config->frequency = 0;
//    m_pTileConfigs->push_back(config);

    config = new lorafel::Tile::TileConfig();
    config->create = std::bind([=](){
        ValueMap args;
        args["tile_image"] = "lame-spider-sword.png";
        args["attack"] = 500;
        args["hit_distance"] = 2;
        args["item_name"] = "Boh Clang";
        args["xp"] = 500;
        args["glow"] = Glow::GREEN;
        auto lootTile = LootTile::create(args);

        return lootTile;
    });
    config->frequency = 10;
    m_pTileConfigs->push_back(config);

    config = new lorafel::Tile::TileConfig();
    config->create = std::bind([=](){
        ValueMap args;
        args["tile_image"] = "bow-arrow.png";
        args["attack"] = 500;
        args["hit_distance"] = 4;
        args["item_name"] = "Jipstick Bow";
        args["xp"] = 500;
        args["glow"] = Glow::PURPLE;
        auto lootTile = LootTile::create(args);

        return lootTile;
    });
    config->frequency = 10;
    m_pTileConfigs->push_back(config);

}

lorafel::Tile::TileConfigs* LootFactory::getBasicLoot() {
    return m_pTileConfigs;
}

lorafel::Tile::TileConfigs* LootFactory::getXpLoot() {
    return new lorafel::Tile::TileConfigs();
}

lorafel::Tile::TileConfigs* LootFactory::getLevelLoot() {
    return new lorafel::Tile::TileConfigs();
}













