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

lorafel::Tile* LootFactory::createTile(lorafel::Tile* pTile = nullptr) {
    lorafel::Tile::TileConfigs* basicLoot = getBasicLoot();
    lorafel::Tile::TileConfigs* xpLoot = getXpLoot();
    lorafel::Tile::TileConfigs* levelLoot = getLevelLoot();


    lorafel::Tile::TileConfigs* allLoot = new lorafel::Tile::TileConfigs();

    if(pTile != nullptr) {
        lorafel::Tile::TileConfigs* tileLoot = pTile->getLoot();
        allLoot->reserve(basicLoot->size() + xpLoot->size() + levelLoot->size() + tileLoot->size());
        allLoot->insert(allLoot->end(), tileLoot->begin(), tileLoot->end());
    } else {
        allLoot->reserve(basicLoot->size() + xpLoot->size() + levelLoot->size());
    }

    allLoot->insert(allLoot->end(), basicLoot->begin(), basicLoot->end());
    allLoot->insert(allLoot->end(), xpLoot->begin(), xpLoot->end());
    allLoot->insert(allLoot->end(), levelLoot->begin(), levelLoot->end());


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

    /**
     * Select a random item class, type,
     * and image from the item tree in
     * the database
     */
    std::string itemClassName, itemTypeName;
    ValueMap itemClass = getRandomValueMapFromValueMap(m_itemTree["items"].asValueMap(), itemClassName);
    ValueMap itemType = getRandomValueMapFromValueMap(itemClass["types"].asValueMap(), itemTypeName);
    ValueMap itemImage = getRandomValueMapFromValueVector(itemType["tile_images"].asValueVector());

    args["item_class"] = itemClassName;
    args["item_type"] = itemTypeName;
    args["tile_image"] = itemImage["tile_image"].asString();

    /**
     * Ensure the name of the item does not
     * exceed 25 characters to prevent
     * window overflow
     */
    std::string name;
    do {
        name = ItemNameGenerator::getInstance()->getName(itemTypeName);
    } while(name.length() > 25);

    args["item_name"] = name;

    /**
     * TODO: Determine glow color based on
     * cumulative stats and attributes. Better
     * item rolls give better color rarities
     */
    args["glow"] = Glow::GREEN;

    /**
     * TODO: Determine the amount of XP given
     * based on cumulative stata and attributes
     */
    args["xp"] = 500;

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

float LootFactory::getRandomMultiplierForItemType(std::string itemClass, std::string itemType) {
    ValueMap items = m_itemTree["items"].asValueMap();
    ValueMap klass = items[itemClass.c_str()].asValueMap();
    ValueMap types = klass["types"].asValueMap();
    ValueMap type = types[itemType.c_str()].asValueMap();
    auto min = type["minmul"].asFloat();
    auto max = type["maxmul"].asFloat();
    return random(min, max);
}













