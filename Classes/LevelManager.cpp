//
// Created by Jarad M DeLorenzo on 11/28/16.
//

#include "LevelManager.h"

using namespace lorafel;

LevelManager* LevelManager::_instance;

void LevelManager::init() {

}

void LevelManager::loadLevelTree(Value data) {
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        m_levelTree = data.asValueMap()["level_tree"].asValueMap();
        CCLOG("LevelManager::loadLevelTree() - Level tree loaded into memory");
        CCLOG("LevelManager::loadLevelTree() - Level tree size=%lu", sizeof(m_levelTree));
    }
}

void LevelManager::loadTileTree(Value data) {
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        m_levelTree = data.asValueMap()["tile_tree"].asValueMap();
        CCLOG("LevelManager::loadTileTree() - Level tree loaded into memory");
        CCLOG("LevelManager::loadTileTree() - Level tree size=%lu", sizeof(m_tileTree));
    }
}

