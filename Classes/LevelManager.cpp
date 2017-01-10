//
// Created by Jarad M DeLorenzo on 11/28/16.
//

#include "LevelManager.h"
#include "StupidRandomizer.h"
#include "TileFactory.h"

using namespace lorafel;

LevelManager* LevelManager::_instance;

void LevelManager::init() {
    m_pLevelTree = new cocos2d::ValueMap();
    m_pTileTree = new cocos2d::ValueMap();
}

void LevelManager::loadLevelTree(cocos2d::Value data) {
    if (!data.isNull() && data.getType() == cocos2d::Value::Type::MAP) {
        *m_pLevelTree = data.asValueMap()["level_tree"].asValueMap();
        CCLOG("LevelManager::loadLevelTree() - Level tree loaded into memory");
        CCLOG("LevelManager::loadLevelTree() - Level tree size=%lu", sizeof(m_pLevelTree));
    }
}

void LevelManager::loadTileTree(cocos2d::Value data) {
    if (!data.isNull() && data.getType() == cocos2d::Value::Type::MAP) {
        *m_pTileTree = data.asValueMap()["tile_tree"].asValueMap();
        CCLOG("LevelManager::loadTileTree() - Tile tree loaded into memory");
        CCLOG("LevelManager::loadTileTree() - Tile tree size=%lu", sizeof(m_pTileTree));
    }
}

Level* LevelManager::createLevel(int levelId) {
    auto levelRoot = m_pLevelTree->at("levels").asValueVector();

    auto levelConfig = levelRoot[levelId].asValueMap();

    m_currentLevelId = levelId;

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
    auto tileSet = levelConfig["tile_set"].asValueVector();
    auto tileDefs = m_pTileTree->at("tiles").asValueMap();

    for(auto tileConfig : tileSet) {
        auto f = tileConfig.asValueMap()["f"].asInt();
        auto id = tileConfig.asValueMap()["id"].asString();
        auto args = tileDefs[id].asValueMap();
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
    auto staticTiles = levelConfig["static"].asValueVector();

    for(auto tileConfig : staticTiles) {
        int x,y;
        auto id = tileConfig.asValueMap()["id"].asString();

        if(!tileConfig.asValueMap()["x"].isNull()) {
            x = tileConfig.asValueMap()["x"].asInt();
        } else {
            x = RandomHelper::random_int(0, SwappyGrid::NUM_COLUMNS-1);
        }

        if(!tileConfig.asValueMap()["y"].isNull()) {
            y = tileConfig.asValueMap()["y"].asInt();
        } else {
            y = RandomHelper::random_int(0, SwappyGrid::NUM_ROWS-1);
        }

        auto args = tileDefs[id].asValueMap();
        level->addStaticTile(std::make_pair(x,y), args);
    }

    setCurrentLevel(level);
    return getCurrentLevel();

}

