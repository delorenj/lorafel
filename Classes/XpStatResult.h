//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_XPSTATRESULT_H
#define LORAFEL_XPSTATRESULT_H

#include "StatResult.h"

namespace lorafel {
    class XpStatResult : public StatResult {
    public:
        XpStatResult(int val) : StatResult(val) { };

        void apply(bool isEnemyTurn) override;

    };
}

#endif //LORAFEL_XPSTATRESULT_H
