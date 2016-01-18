//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_STATRESULT_H
#define LORAFEL_STATRESULT_H

#import "MatchResult.h"

namespace lorafel {
    class StatResult : public MatchResult<int> {
    public:
        StatResult(int val) : MatchResult(val) { };
        virtual ~StatResult() { };
        virtual void apply() = 0;
        void setMultiplier(const int val) { m_multiplier = val; }
        int getMultiplier() const { return m_multiplier; }

    protected:
        int m_multiplier = 1;
    };
}
#endif //LORAFEL_STATRESULT_H
