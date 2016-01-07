//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "Match.h"

using namespace lorafel;

Match::Match() {

}

Match::~Match() {

}

const std::vector<MatchResult<int>*> &Match::getStatResults() const {
    return m_pMatchResults;
}

void Match::addTile(Tile* tile) {
    m_pTileSet.insert(tile);
}

void Match::setTileSet(const std::set<Tile *> &tileSet) {
    m_pTileSet = tileSet;
}

const std::set<Tile *> &Match::getTileSet() const {
    return m_pTileSet;
}

void Match::run() {
    CCLOG("APPLYING Match Results");
    std::vector<MatchResult<int>*> results = getStatResults();
    for(MatchResult<int>* mr : results) {
        mr->apply();
    }
}
