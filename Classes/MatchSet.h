//
// Created by Jarad DeLorenzo on 6/3/16.
//

#ifndef LORAFEL_MATCHSET_H
#define LORAFEL_MATCHSET_H

#include "Match.h"

namespace lorafel {
    class MatchSet : public std::set<Match*> {
    public:
        MatchSet& unique();
    };
}

#endif //LORAFEL_MATCHSET_H
