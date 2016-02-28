//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "Level.h"

using namespace lorafel;

Tile* Level::getRandomTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    int result = randomizer->randomize(probs);
    return m_pTileConfigs->at(result)->factory->createTile();
}

/**
 * Basic levelCleared test: no monsters left
 * Other strategies could be "killed 10 monsters
 * in 5 tries", or "killed all monsters in under X time"
 */
bool Level::isCleared() const {
    return m_pSwappyGrid->getNumberOfRemainingEnemies() == 0;
}

TurnManager* Level::getTurnManager() {
    return m_pTurnManager;
}
