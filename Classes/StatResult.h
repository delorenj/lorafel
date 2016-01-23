//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_STATRESULT_H
#define LORAFEL_STATRESULT_H

#import "MatchResult.h"
#include "Match.h"

namespace lorafel {
    class Match;
    class StatResult : public MatchResult<int> {
    public:
        StatResult(int val) : MatchResult(val) { };
        virtual ~StatResult() { };
        virtual void apply() = 0;
        void setMultiplier(const int val) { m_multiplier = val; }
        int getMultiplier() const { return m_multiplier; }
        void setMatch(Match* pMatch) { m_pMatch = pMatch; }

    protected:
        int m_multiplier = 1;
        Match* m_pMatch;
    };
}
#endif //LORAFEL_STATRESULT_H
