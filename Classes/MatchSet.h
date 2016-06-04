//
// Created by Jarad DeLorenzo on 6/3/16.
//

#ifndef LORAFEL_MATCHSET_H
#define LORAFEL_MATCHSET_H

#include "Match.h"

namespace lorafel {
    class MatchSet {
    public:
        std::set<lorafel::Match*> unique();

        std::pair<std::set<lorafel::Match*>::iterator,bool> insert(lorafel::Match* match);

    protected:
        std::set<lorafel::Match*> m_set;
    };
}

#endif //LORAFEL_MATCHSET_H
