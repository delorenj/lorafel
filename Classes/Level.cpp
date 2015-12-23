//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "Level.h"

using namespace lorafel;

Level::Level() {

}

Level::~Level() {

}

Tile* Level::getRandomTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    int result = randomizer->randomize(probs);
    return m_pTileConfigs->at(result)->factory->createTile();
}
