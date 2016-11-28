//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_ENEMYTILE_H
#define LORAFEL_ENEMYTILE_H

#include "Tile.h"
#include "Globals.h"

namespace lorafel {
    class EnemyTile : public Tile {
    public:
        bool init(cocos2d::ValueMap args) override;

        virtual void onMatch(Match* pMatch) override;
        virtual void onHit(cocos2d::EventCustom* event);
        virtual void remove() override;

        void decreaseHpBy(int amount);

//        virtual void applyHit(Match* pMatch);
        virtual void applyHit(int hitAmount);

        virtual const unsigned int getMinMatchSize() const override { return MIN_MATCH_SIZE+1; }
        virtual Tile* getRandomGlyph();
        virtual bool isSwappable() override;
        virtual bool isMatch(Tile* pTile) const override {
            // Enemy tile matches all tiles except loot, hero
            return (pTile->getTag() != Tag::HERO) && (pTile->getTag() != Tag::LOOT);
        };
        virtual bool freelyMovable() override { return true; }

    protected:
        TileConfigs* m_pTileConfigs;
    };
}

#endif //LORAFEL_ENEMYTILE_H
