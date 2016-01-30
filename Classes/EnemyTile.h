//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_ENEMYTILE_H
#define LORAFEL_ENEMYTILE_H

#include "Tile.h"

namespace lorafel {
    class EnemyTile : public Tile {
    public:
        EnemyTile();

        virtual void onMatch(Match* pMatch) override;
        virtual void onHit(cocos2d::EventCustom* event);
        virtual void remove() override;

        void decreaseHpBy(int amount);

        virtual void applyHit(Match* pMatch);

        void setHp(int hp) { m_hp = hp; }

        int getHp() const { return m_hp; }

        virtual bool isMatch(Tile* pTile) const override {
            // Enemy tile matches all tiles for now
            return true;
        };

        virtual bool isEnemy() override { return true; }

    protected:
        int m_hp;

    };

}

#endif //LORAFEL_ENEMYTILE_H