//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_XPMATCHRESULT_H
#define LORAFEL_XPMATCHRESULT_H

#include "MatchResult.h"

namespace lorafel {
    class XpMatchResult : public MatchResult<int> {
    public:
        XpMatchResult(int val) : MatchResult(val) {
        }

        virtual ~XpMatchResult() {};

        void apply() override;

    };
}

#endif //LORAFEL_XPMATCHRESULT_H
