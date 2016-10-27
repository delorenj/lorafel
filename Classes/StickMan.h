//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_STICKMAN_H
#define LORAFEL_STICKMAN_H

#include "EnemyTile.h"

namespace lorafel {
    class StickMan : public EnemyTile {
    public:
        virtual bool init() override;
        CREATE_FUNC(StickMan);

//        virtual void applyHit(Match* pMatch) override;

    protected:
        /**
         * Overriding this so this enemy is easier. He will sometimes
         * drop normal tiles mixed in with the mean glyphs
         */
        Tile* getRandomGlyph() override;
    };
}

#endif //LORAFEL_STICKMAN_H
