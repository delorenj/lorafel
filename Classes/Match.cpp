//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "Match.h"
#include "XpStatResult.h"
#include "GameStateMachine.h"

using namespace lorafel;

void Match::setTileSet(std::set<Tile *>* tileSet) {
    m_pTileSet = tileSet;
}

std::set<Tile *>* Match::getTileSet() const {
    return m_pTileSet;
}

void Match::run() {
    // Get a single tile from the set
    // to extract reward stats
    auto tile = *m_pTileSet->begin();
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
        tile->remove();
    }

    GameStateMachine::getInstance()->enterState<TileRemovedState>();

}

cocos2d::Vec2 Match::getTileSetCenter() {
    auto tile = *m_pTileSet->begin();
    return tile->getGrid()->convertToWorldSpace(cocos2d::Vec2(tile->getPosition().x + tile->getContentSize().width/2, tile->getPosition().y + tile->getContentSize().height/2));
}
