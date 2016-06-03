//
// Created by Jarad DeLorenzo on 6/3/16.
//

#include "MatchSet.h"

using namespace lorafel;

std::set<Match*> MatchSet::unique() {
    return m_set;
}

std::pair<std::set<Match*>::iterator, bool> MatchSet::insert(Match* match) {
    for(auto set : m_set) {
        bool fullMatch = false;
        std::set<Tile*>* tiles = match->getTileSet();
        for(auto t : *tiles) {
            auto it = set.find(t);
        }
    }
    return m_set.insert(match);
}





