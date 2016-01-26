//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "Match.h"
#include "XpStatResult.h"
#include "GameStateMachine.h"
#include "EnemyTile.h"

using namespace lorafel;

void Match::setTileSet(std::set<Tile *>* tileSet) {
    m_pTileSet = tileSet;
}

std::set<Tile *>* Match::getTileSet() const {
    return m_pTileSet;
}

void Match::run() {

    auto tile = getPrimaryTile();

    std::set<StatResult*>* results = tile->getStatResults();

    // Iterate through all tile stat results
    // and apply them to your score/XP/HP/etc...
    for(StatResult* mr : *results) {
        mr->setMultiplier(m_pTileSet->size());
        mr->setMatch(this);
        mr->apply();
    }

    // Iterate through each tile in the match
    // set and remove it from the grid
    for(auto tile : *m_pTileSet) {
        tile->onMatch(this);
    }

    GameStateMachine::getInstance()->enterState<TileRemovedState>();

}

cocos2d::Vec2 Match::getTileSetCenter() {
    auto tile = *m_pTileSet->begin();
    return tile->getGrid()->convertToWorldSpace(cocos2d::Vec2(tile->getPosition().x + tile->getContentSize().width/2, tile->getPosition().y + tile->getContentSize().height/2));
}

TileFactory* Match::getPrimaryTileFactory() const {
    // If it's set, return it
    if(m_pPrimaryTileFactory != nullptr) {
        return m_pPrimaryTileFactory;
    }

    // If not set yet, then find it
    // Get a single tile from the set
    // to extract reward stats
    auto tileIter = m_pTileSet->begin();

    // Make sure we get a non-enemy
    // Todo: Handle only-enemy matches
    while(tileIter != m_pTileSet->end()) {
        auto tile = *tileIter;
        if(!tile->isEnemy()) {
            break;
        } else {
            tileIter++;
        }
    }

    return *tileIter->getFactory();

    }
}

unsigned long Match::getTileSetSize() {
    return m_pTileSet->size();
}

unsigned int Match::getNumEnemies() {
    auto it = m_pTileSet->begin();
    int numEnemies = 0;
    while(it != m_pTileSet->end()) {
        auto tile = *it;
        if(tile->isEnemy()) {
            numEnemies++;
        }
    }
    return numEnemies;
}
