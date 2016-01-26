//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_STICKMAN_H
#define LORAFEL_STICKMAN_H

#include "EnemyTile.h"

namespace lorafel {
    class StickMan : public EnemyTile {
    public:
        static StickMan* create();
        virtual void applyHit(Match* pMatch) override;
    };
}

#endif //LORAFEL_STICKMAN_H
