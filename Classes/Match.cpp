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
        mr->apply();
    }

    // Iterate through each tile in the match
    // set and remove it from the grid
    for(auto tile : *m_pTileSet) {
        tile->remove();
    }

    GameStateMachine::getInstance()->enterState<TileRemovedState>();

}
