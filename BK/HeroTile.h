//
// Created by Jarad DeLorenzo on 2/3/16.
//

#ifndef LORAFEL_AVATAR_H
#define LORAFEL_AVATAR_H

#include "Tile.h"

namespace lorafel {
    class HeroTile : public Tile {
    public:
        bool init() override;
        static HeroTile* create(const char string[100]);
        virtual void onMatch(Match* pMatch) override;
        virtual void onHit(cocos2d::EventCustom* event);
        virtual void remove() override;

        void decreaseHpBy(int amount);

        virtual void applyHit(Match* pMatch);

        virtual bool isMatch(Tile* pTile) const override {
            // Enemy tile matches all tiles for now
            return true;
        };

    };
}

#endif //LORAFEL_AVATAR_H