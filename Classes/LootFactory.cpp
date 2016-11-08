//
// Created by Jarad DeLorenzo on 4/13/16.
//

#include "Globals.h"
#include "LootFactory.h"
#include "LootTile.h"
#include "LinearWeightedRandomizer.h"

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

/**
 * I feel as though this should be part of the Item
 * instead of having an if/else here for each item
 */
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

    if(!itemType["equip_masks"].isNull()) {
        args["equip_masks"] = itemType["equip_masks"];
    }

    args["item_class"] = itemClassName;
    args["item_type"] = itemTypeName;
    args["tile_image"] = itemImage["tile_image"].asString();

    /**
     * Determine some extra
     * attributes
     */
    rollExtraAttributes(args);

    std::string name;
    if(itemType["name"].isNull()) {
        /**
         * Ensure the name of the item does not
         * exceed 25 characters to prevent
         * window overflow
         */
        do {
            name = ItemNameGenerator::getInstance()->getName(itemTypeName);
        } while(name.length() > 25);
    } else {
        /**
         * If name is provided in the itemType
         * section, then use that instead of
         * generating an item name.
         */
        name = itemType["name"].asString();
    }

    args["item_name"] = name;

    /**
     * Roll all class/type-specific stats
     */
    if(itemClassName == "Weapon") {
        rollAttack(args);
        rollHitDistance(args);
    } else
    if(itemClassName == "HealthPotion") {
        args["amount"] = itemType["amount"];
    } else
    if(itemClassName == "Armor") {
        rollDefend(args);
    }

    /**
     * TODO: Determine the amount of XP given
     * based on cumulative state and attributes
     */


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

Value LootFactory::getRandomValueFromValueVector(ValueVector& inValueVector) {
    auto idx = RandomHelper::random_int(0, (int)inValueVector.size()-1);
    return inValueVector.at(idx);
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

int LootFactory::getRandomHitDistanceForItemType(std::string itemClass, std::string itemType) {
    if(itemClass != "Weapon") {
        return 0;
    }

    ValueMap items = m_itemTree["items"].asValueMap();
    ValueMap klass = items[itemClass.c_str()].asValueMap();
    ValueMap types = klass["types"].asValueMap();
    ValueMap type = types[itemType.c_str()].asValueMap();
    auto min = type["minhd"].asInt();
    auto max = type["maxhd"].asInt();
    return random(min, max);
}

std::string LootFactory::getRandomAttributeForItemClass(std::string itemClass) {
    ValueMap items = m_itemTree["items"].asValueMap();
    ValueMap klass = items[itemClass.c_str()].asValueMap();
    if(klass["attributes"].isNull()) {
        return "none";
    }

    ValueVector attributes = klass["attributes"].asValueVector();
    return getRandomValueFromValueVector(attributes).asString();
}

void LootFactory::rollExtraAttributes(ValueMap& args) {
    CCLOG("LootFactory::rollExtraAttributes() - Rolling extra attributes for item %s", args["item_name"].asString().c_str());
    std::vector<int> bucket(4);
    int numAttr;
    
    auto rand = CCRANDOM_0_1();
    if(rand < 0.01) {
        numAttr = 3;
    } else if(rand < 0.10) {
        numAttr = 2;
    } else if(rand < 0.4) {
        numAttr = 1;
    } else {
        return;
    }

    CCLOG("LootFactory::rollExtraAttributes() - Lucky player gets %d attributes for item %s", numAttr, args["item_name"].asString().c_str());
    ValueVector attrs;

    std::map<std::string, int> attrmap;
    for(int i=0; i<numAttr; i++) {
        rollAttribute(args);
    }
}

int LootFactory::getIntegerAttributeParam(std::string attr, std::string param) {
    auto attributes = m_itemTree["attributes"].asValueMap();
    auto attribute = attributes[attr].asValueMap();
    auto val = attribute[param].asInt();
    return val;
}

void LootFactory::rollAttack(ValueMap& args) {
    CCLOG("LootFactory::rollAttack() - Rolling attack for item %s", args["item_name"].asString().c_str());
    int baseAttack = PlayerManager::getInstance()->getPlayer()->getBaseAttack();
    CCLOG("baseAttack=%d", baseAttack);
    /** Get base attack for class/type */
    float multiplier = getRandomMultiplierForItemType(args["item_class"].asString(), args["item_type"].asString());
    CCLOG("multiplier=%f", multiplier);
    int attack = ROUND_2_INT(baseAttack * multiplier);
    CCLOG("attack=%d", attack);
    args["attack"] = attack;
}

void LootFactory::rollDefend(ValueMap& args) {
    CCLOG("LootFactory::rollDefend() - Rolling defend for item %s", args["item_name"].asString().c_str());
    int baseDefend = PlayerManager::getInstance()->getPlayer()->getBaseDefend();
    CCLOG("baseDefend=%d", baseDefend);
    /** Get base defend for class/type */
    float multiplier = getRandomMultiplierForItemType(args["item_class"].asString(), args["item_type"].asString());
    CCLOG("multiplier=%f", multiplier);
    int defend = ROUND_2_INT(baseDefend * multiplier);
    CCLOG("defend=%d", defend);
    args["defend"] = defend;
}

/**
 * TODO: Refactor to use interface for determining
 * it item implements Hit Distance
 */
void LootFactory::rollHitDistance(ValueMap& args) {
    /** Hit distance only makes sense for weapons */
    CCLOG("LootFactory::rollHitDistance() - Rolling hit_distance for item %s", args["item_name"].asString().c_str());
    int hd = getRandomHitDistanceForItemType(args["item_class"].asString(), args["item_type"].asString());
    CCLOG("hit_distance=%d", hd);
    args["hit_distance"] = hd;
}

void LootFactory::rollPotionAmount(ValueMap &args) {
    CCLOG("LootFactory::rollPotionAmount() - Rolling potionAmount for item %s", args["item_name"].asString().c_str());
    /** Get base potionAmount for class/type */
    float amount = getRandomMultiplierForItemType(args["item_class"].asString(), args["item_type"].asString());
    CCLOG("amount=%f", amount);
    args["amount"] = amount;
}

void LootFactory::rollAttribute(ValueMap &args) {
    std::string attr;
    int tries = 0;

    if(!args["attributes"].isNull()) {
        /**
         * Cap the amount of attributes at 3
         */
        if(args["attributes"].asValueVector().size() >=3 ) return;
        
        auto existingAttrs = args["attributes"].asValueVector();
        bool foundMatch;
        do {
            tries++;
            attr = getRandomAttributeForItemClass(args["item_class"].asString());
            foundMatch = 0;
            for(auto existingAttr : existingAttrs) {
                if( existingAttr.asValueMap()["name"].asString() == attr ) {
                    foundMatch = 1;
                    break;
                }
            }
        } while(tries <= 10 && foundMatch == 1);

    } else {
        attr = getRandomAttributeForItemClass(args["item_class"].asString());
        args["attributes"] = cocos2d::ValueVectorNull;
    }

    /**
     * If item has no attributes
     * then just return early
     */
    if(tries >= 10 || attr == "none") {
        return;
    }
    auto min = getIntegerAttributeParam(attr, "min");
    auto max = getIntegerAttributeParam(attr, "max");
    LinearWeightedRandomizer randomizer;
    int val = randomizer.randomize(min, max, 50.0);
    ValueMap vm;
    vm["name"] = attr;
    vm["value"] = val;
    Value attrVal(vm);
    args["attributes"].asValueVector().push_back(attrVal);
    CCLOG("LootFactory::rollExtraAttribute() - %s with value %d", vm["name"].asString().c_str(), vm["value"].asInt());
}

void LootFactory::rollImprovedAttack(ValueMap& args) {
    LinearWeightedRandomizer randomizer;
    ValueMap items = m_itemTree["items"].asValueMap();
    ValueMap klass = items[args["item_class"].asString().c_str()].asValueMap();
    ValueMap types = klass["types"].asValueMap();
    ValueMap type = types[args["item_type"].asString().c_str()].asValueMap();
    auto max = type["maxmul"].asFloat();

    auto itemLevel = args["level"].isNull() ? 1 : args["level"].asInt();
    float mul = 1.0;
    switch(itemLevel) {
        case 1:
            mul = randomizer.randomize(5, 8);
            break;
        case 2:
            mul = randomizer.randomize(8, 12);
            break;
        case 3:
            mul = randomizer.randomize(12, 15);
            break;
        default:
            mul = 1; // no improvement above level 3
    }

    auto increment = (max * (mul/100));
    CCLOG("LootFactory::rollImprovedAttack - Increasing attack multiplier using equation (%f * (%f/100)) = %f", max, mul, increment);
    CCLOG("LootFactory::rollImprovedAttack - Increasing attack: Current = %d, New = %f",
            args["attack"].asInt(),
            args["attack"].asInt() + ROUND_2_INT(args["attack"].asInt() * mul)
    );
    args["attack"] = args["attack"].asInt() + ROUND_2_INT(args["attack"].asInt() * increment);
}

void LootFactory::rollImprovedHitDistance(ValueMap& args) {

}

const int LootFactory::calculateGlowFromArgs(ValueMap args) {
    /**
     * TODO: Determine glow color based on
     * cumulative stats and attributes. Better
     * item rolls give better color rarities
     */
     if(!args["attributes"].isNull()) {
         switch(args["attributes"].asValueVector().size()) {
             case 1:
                 return Glow::GREEN;
             case 2:
                 return Glow::YELLOW;
             case 3:
                 return Glow::BLUE;
             default:
                 return Glow::NONE;
         };
     }
}

int LootFactory::calculateXpFromArgs(ValueMap args) {
    /**
     * TODO: Balance this so higher levels get
     * a little more (or something)
     */
    if(!args["attributes"].isNull()) {
        switch(args["attributes"].asValueVector().size()) {
            case 1:
                return 250;
            case 2:
                return 600;
            case 3:
                return 1250;
            default:
                100;
        };
    }
}

void LootFactory::rollImprovedDefend(ValueMap &args) {
    LinearWeightedRandomizer randomizer;
    ValueMap items = m_itemTree["items"].asValueMap();
    ValueMap klass = items[args["item_class"].asString().c_str()].asValueMap();
    ValueMap types = klass["types"].asValueMap();
    ValueMap type = types[args["item_type"].asString().c_str()].asValueMap();
    auto max = type["maxmul"].asFloat();

    auto itemLevel = args["level"].isNull() ? 1 : args["level"].asInt();
    float mul = 1.0;
    switch(itemLevel) {
        case 1:
            mul = randomizer.randomize(5, 8);
            break;
        case 2:
            mul = randomizer.randomize(8, 12);
            break;
        case 3:
            mul = randomizer.randomize(12, 15);
            break;
        default:
            mul = 1; // no improvement above level 3
    }

    auto increment = (max * (mul/100));
    CCLOG("LootFactory::rollImprovedDefend - Increasing defend multiplier using equation (%f * (%f/100)) = %f", max, mul, increment);
    CCLOG("LootFactory::rollImprovedDefend - Increasing defend: Current = %d, New = %f",
            args["defend"].asInt(),
            args["defend"].asInt() + ROUND_2_INT(args["defend"].asInt() * mul)
    );
    args["defend"] = args["defend"].asInt() + ROUND_2_INT(args["defend"].asInt() * increment);
}








