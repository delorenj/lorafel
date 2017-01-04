//
// Created by Jarad M DeLorenzo on 11/28/16.
//

#include "LevelManager.h"
#include "StupidRandomizer.h"
#include "TileFactory.h"

using namespace lorafel;

LevelManager* LevelManager::_instance;

void LevelManager::init() {
}

void LevelManager::loadLevelTree(cocos2d::Value data) {
    if (!data.isNull() && data.getType() == cocos2d::Value::Type::MAP) {
        m_levelTree = data.asValueMap()["level_tree"].asValueMap();
        CCLOG("LevelManager::loadLevelTree() - Level tree loaded into memory");
        CCLOG("LevelManager::loadLevelTree() - Level tree size=%lu", sizeof(m_levelTree));
    }
}

void LevelManager::loadTileTree(cocos2d::Value data) {
    if (!data.isNull() && data.getType() == cocos2d::Value::Type::MAP) {
        m_tileTree = data.asValueMap()["tile_tree"].asValueMap();
        CCLOG("LevelManager::loadTileTree() - Tile tree loaded into memory");
        CCLOG("LevelManager::loadTileTree() - Tile tree size=%lu", sizeof(m_tileTree));
    }
}

Level* LevelManager::createLevel(int levelId) {
    cocos2d::ValueVector levelRoot = (std::vector<Value> &&) m_levelTree["levels"].asValueVector();

    cocos2d::ValueMap levelConfig = (std::unordered_map<std::string, Value> &&) levelRoot[levelId].asValueMap();

    Level* level = new Level();
    level->setSwappyGrid(m_pSwappyGrid);
    level->addTransparencyGrid();

    /**
     * Set the level's background image
     */
    if(!levelConfig["bg"].isNull()) {
        level->setImage(levelConfig["bg"].asString());
    }

    /**
     * Create and set the desired randomization strategy
     */
    if(!levelConfig["randomizer"].isNull()) {
        auto randomizer = levelConfig["randomizer"].asString();
        if(randomizer == "StupidRandomizer") {
            level->setRandomizer(new StupidRandomizer());
        } else {
            level->setRandomizer(new NormalDistributionRandomizer());
        }
    } else {
        level->setRandomizer(new NormalDistributionRandomizer());
    }

    if(!levelConfig["turn_manager"].isNull()) {
        auto tm = levelConfig["turn_manager"].asString();
        if(tm == "BasicTurnManager") {
            level->setTurnManager(new BasicTurnManager());
        } else {
            // There are no other turn managers implemented yet!
            CCLOG("LevelMananger::createLevel() - Tried to load %s, but there are no other TurnManagers implemented yet. Loading BasicTurnManager", tm.c_str());
            level->setTurnManager(new BasicTurnManager());
        }
    } else {
        level->setTurnManager(new BasicTurnManager());
    }


    /**
     * Random Tiles
     */
    auto tileSet = (std::vector<Value> &&) levelConfig["tile_set"].asValueVector();
    auto tileDefs = (std::unordered_map<std::string, Value> &&) m_tileTree["tiles"].asValueMap();

    for(auto tileConfig : tileSet) {
        auto f = tileConfig.asValueMap()["f"].asInt();
        auto id = tileConfig.asValueMap()["id"].asString();
        auto args = (std::unordered_map<std::string, Value> &&) tileDefs[id].asValueMap();
        auto config = new Tile::TileConfig();

        config->create = std::bind([=]() {
           return  TileFactory::getInstance()->create(args);
        });

        config->frequency = f;
        level->addTileConfig(config);
    }

    /**
     * Static Tiles
     */
    auto staticTiles = (std::vector<Value> &&) levelConfig["static"].asValueVector();

    for(auto tileConfig : staticTiles) {
        int x,y;
        auto id = tileConfig.asValueMap()["id"].asString();

        if(!tileConfig.asValueMap()["x"].isNull()) {
            x = tileConfig.asValueMap()["x"].asInt();
        } else {
            x = RandomHelper::random_int(0, SwappyGrid::NUM_COLUMNS);
        }

        if(!tileConfig.asValueMap()["y"].isNull()) {
            y = tileConfig.asValueMap()["y"].asInt();
        } else {
            y = RandomHelper::random_int(0, SwappyGrid::NUM_ROWS);
        }

        auto args = (std::unordered_map<std::string, Value> &&) tileDefs[id].asValueMap();
        level->addStaticTile(std::make_pair(x,y), args);
    }

    setCurrentLevel(level);
    return getCurrentLevel();

}

