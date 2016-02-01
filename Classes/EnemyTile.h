//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_ENEMYTILE_H
#define LORAFEL_ENEMYTILE_H

#include "Tile.h"

namespace lorafel {
    class EnemyTile : public Tile {
    public:
        bool init() override;

        virtual void onMatch(Match* pMatch) override;
        virtual void onHit(cocos2d::EventCustom* event);
        virtual void remove() override;

        void decreaseHpBy(int amount);

        virtual void applyHit(Match* pMatch);

        virtual bool isMatch(Tile* pTile) const override {
            // Enemy tile matches all tiles for now
            return true;
        };

        virtual bool isEnemy() override { return true; }

    };

}

#endif //LORAFEL_ENEMYTILE_H
