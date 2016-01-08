//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "Match.h"
#include "XpMatchResult.h"

using namespace lorafel;

Match::Match() {

}

Match::~Match() {

}

const std::vector<StatResult*> Match::getStatResults() const {
    auto xp = new XpMatchResult(5);
    auto xxp = new XpMatchResult(10);
    std::vector<StatResult*> res;
    res.push_back(xp);
    res.push_back(xxp);
    return res;
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
    std::vector<StatResult*> results = getStatResults();
    for(StatResult* mr : results) {
        mr->apply();
        CC_SAFE_DELETE(mr);
    }
}
