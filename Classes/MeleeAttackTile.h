//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_BEARTILE_H
#define LORAFEL_BEARTILE_H

#include "Tile.h"

namespace lorafel {
    class MeleeAttackTile : public Tile {
    public:
        MeleeAttackTile();
        ~MeleeAttackTile();

        static MeleeAttackTile* create();

        void onMatch(Match* pMatch) override;
    };
}
#endif //LORAFEL_BEARTILE_H
