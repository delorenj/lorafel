//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_GOLDSTATRESULT_H
#define LORAFEL_GOLDSTATRESULT_H

#include "StatResult.h"

namespace lorafel {
    class GoldStatResult : public StatResult {
    public:
        GoldStatResult(int val) : StatResult(val) { };

        void apply(bool isEnemyTurn = 0) override;

    };
}

#endif //LORAFEL_GOLDSTATRESULT_H
