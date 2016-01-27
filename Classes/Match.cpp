//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "Match.h"
#include "XpStatResult.h"
#include "GameStateMachine.h"

using namespace lorafel;

Match::~Match() {
    for(auto it : *m_pTileSet) {
        CC_SAFE_DELETE(it);
    }
}

void Match::setTileSet(std::set<Tile *>* tileSet) {
    m_pTileSet = tileSet;
    m_pEnemies = new std::set<Tile*>();

    auto it = m_pTileSet->begin();
    while(it != m_pTileSet->end()) {
        auto t = static_cast<Tile*>(*it);
        if(t->isEnemy()) {
            m_pEnemies->insert(*it);
        } else if(m_pPrimaryTile == nullptr) {
            m_pPrimaryTile = *it;
        }
        it++;
    }
    CCLOG("EnemyCount: %d", m_pEnemies->size());
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

Tile* Match::getPrimaryTile() const {
    return m_pPrimaryTile;
}

unsigned long Match::getTileSetSize() {
    return m_pTileSet->size();
}

unsigned long Match::getNumEnemies() {
    return m_pEnemies->size();
}

std::set<Tile*>* Match::getEnemies() const {
    return m_pEnemies;
}
