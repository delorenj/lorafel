//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "Level.h"
#include "LootFactory.h"
#include "TileFactory.h"
#include "LevelClearedUI.h"

using namespace lorafel;

lorafel::Tile* Level::getRandomTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    int result = m_pRandomizer->randomize(probs);
    return m_pTileConfigs->at(result)->create();
}

/**
 * Basic levelCleared test: no monsters left
 * Other strategies could be "killed 10 monsters
 * in 5 tries", or "killed all monsters in under X time"
 */
bool Level::isCleared() const {
    return m_pSwappyGrid->getNumberOfRemainingEnemies() == 0 && m_pSwappyGrid->tileDropQueuesEmpty();
}

TurnManager* Level::getTurnManager() {
    return m_pTurnManager;
}

lorafel::Tile* Level::getRandomLoot(Tile* sourceTile) {
    /**
     * Before we create a loot tile, since loot is level-based
     * and player based, we can finnagle around with the LootFactory
     * settings to customize the loot generated based on the tile
     * passed in. For now, let's just try it plain-style
     */
    return LootFactory::getInstance()->createTile();
}

lorafel::Tile * Level::createTileFromGridPos(int x, int y) {
    for(auto entry : m_staticTiles) {
        auto pos = entry.first;
        auto tileArgs = entry.second;

        if(pos.first == x && pos.second == y) {
            return TileFactory::getInstance()->create(tileArgs);
        }
    }

    return nullptr;
}

void Level::addTransparencyGrid() {
    /**
     * Insert background transparency tiles
     */
    for (int i = 0; i < SwappyGrid::NUM_COLUMNS; i++) {
        for (int j = 0; j < SwappyGrid::NUM_ROWS; j++) {
            GridTransparency::Tile::Color color = (i + j) % 2 == 0 ? GridTransparency::Tile::Color::LIGHT : GridTransparency::Tile::Color::DARK;
            GridTransparency::Tile::Type type;

            if (i == 0 && j == SwappyGrid::NUM_ROWS - 1) { // TopLeft
                type = GridTransparency::Tile::Type::TOP_LEFT;
            } else if (i == 0 && j > 0 && j < SwappyGrid::NUM_ROWS - 1) {
                type = GridTransparency::Tile::Type::LEFT;
            } else if (i == 0 && j == 0) {
                type = GridTransparency::Tile::Type::BOTTOM_LEFT;
            } else if (i > 0 && j == 0 && i < SwappyGrid::NUM_COLUMNS - 1) {
                type = GridTransparency::Tile::Type::BOTTOM;
            } else if (j == 0 && i == SwappyGrid::NUM_COLUMNS - 1) {
                type = GridTransparency::Tile::Type::BOTTOM_RIGHT;
            } else if (j < SwappyGrid::NUM_ROWS - 1 && j > 0 && i == SwappyGrid::NUM_COLUMNS - 1) {
                type = GridTransparency::Tile::Type::RIGHT;
            } else if (j == SwappyGrid::NUM_ROWS - 1 && i == SwappyGrid::NUM_COLUMNS - 1) {
                type = GridTransparency::Tile::Type::TOP_RIGHT;
            } else if (i > 0 && i < SwappyGrid::NUM_COLUMNS - 1 && j == SwappyGrid::NUM_ROWS - 1) {
                type = GridTransparency::Tile::Type::TOP;
            } else {
                type = GridTransparency::Tile::Type::CENTER;
            }

            m_pSwappyGrid->getGridTransparency()->insertTile(
                    m_pSwappyGrid->gridToScreen(i, j),
                    GridTransparency::Tile(color, type)
            );
        }
    }
}

void Level::addStaticTile(std::pair<int, int> pos, ValueMap args) {
    m_staticTiles[pos] = args;
}

void Level::onLevelCleared() {
    GameStateMachine::getInstance()->enterState<LevelClearedState>();
    LevelClearedUI::create()->show();
    PlayerManager::getInstance()->getPlayer()->getProgress()
            ->setLevelScore(3)
            ->save();
}
