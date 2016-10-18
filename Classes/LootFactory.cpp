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

    config = new lorafel::Tile::TileConfig();

    config->create = std::bind([&](){
//        args["tile_image"] = "lame-spider-sword.png";
//        args["attack"] = 500;
//        args["hit_distance"] = 2;
//        args["item_name"] = "Boh Clang";
//        args["xp"] = 500;
//        args["glow"] = Glow::GREEN;
        ValueMap args = generateRandomItemArgs();
        return LootTile::create(args);
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

ValueMap LootFactory::generateRandomItemArgs() {
    ValueMap args;

    std::string itemClassName, itemTypeName;
    ValueMap itemClass = getRandomValueMapFromValueMap(m_itemTree["items"].asValueMap(), itemClassName);
    ValueMap itemType = getRandomValueMapFromValueMap(itemClass["types"].asValueMap(), itemTypeName);
    ValueMap itemImage = getRandomValueMapFromValueVector(itemType["tile_images"].asValueVector());

    CCLOG("ItemImage Selected=%s", itemImage["tile_image"].asString().c_str());

    args["item_class"] = itemClassName;
    args["item_type"] = itemTypeName;
    args["tile_image"] = itemImage["tile_image"].asString();
    args["attack"] = 500;
    args["hit_distance"] = 2;
    args["item_name"] = ItemNameGenerator::getInstance()->getName(itemClassName);
    args["xp"] = 500;
    args["glow"] = Glow::GREEN;
    return args;
}

void LootFactory::loadItemTree(Value data) {
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        m_itemTree = data.asValueMap();
        CCLOG("LootFactory::loadItemTree() - Item tree loaded into memory");
        CCLOG("LootFactory::loadItemTree() - Item tree size=%lu", sizeof(m_itemTree));
    }
}

ValueMap LootFactory::getRandomValueMapFromValueMap(ValueMap& inValueMap, std::string& outKey) {
    auto idx = RandomHelper::random_int(0, (int)inValueMap.size()-1);
    auto iter = inValueMap.begin();
    std::advance(iter, idx);
    outKey = iter->first;
    return iter->second.asValueMap();

}

ValueMap LootFactory::getRandomValueMapFromValueVector(ValueVector& inValueVector) {
    auto idx = RandomHelper::random_int(0, (int)inValueVector.size()-1);
    return inValueVector.at(idx).asValueMap();
}













