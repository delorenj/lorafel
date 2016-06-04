//
// Created by Jarad DeLorenzo on 6/3/16.
//

#include "MatchSet.h"

using namespace lorafel;

std::set<Match*> MatchSet::unique() {
    return m_set;
}

std::pair<std::set<lorafel::Match*>::iterator, bool> MatchSet::insert(lorafel::Match* match) {
    std::set<Tile*>* tiles = match->getTileSet();

    for(auto setit = m_set.begin(); setit != m_set.end(); setit++) {
        bool chops = true;
        Match* currMatch = static_cast<Match*>(*setit);
        auto ts = currMatch->getTileSet();
        for(auto tile : *ts) {
            auto it = tiles->find(tile);
            if(it == tiles->end()) chops = false;
        }
        if(chops) return std::pair<std::set<lorafel::Match*>::iterator, bool>(setit, false);
    }
    return m_set.insert(match);
}





