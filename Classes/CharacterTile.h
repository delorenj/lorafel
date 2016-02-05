//
// Created by Jarad DeLorenzo on 2/4/16.
//

#ifndef LORAFEL_CHARACTERTILE_H
#define LORAFEL_CHARACTERTILE_H

#include "Tile.h"
#include "AIStrategy.h"

namespace lorafel {


    class CharacterTile : public Tile {

    public:
        virtual bool init() override { return true; }
        virtual void applyHit(lorafel::Match *pMatch);
        virtual void onHit(cocos2d::EventCustom *event);
        virtual void onMatch(lorafel::Match *pMatch) override;
        virtual void remove() override;

        virtual bool isSwappable() { return false; }
        virtual bool isMatch(lorafel::Tile *pTile) const override {
            // Character tiles match all tiles for now
            return true;
        }

        virtual AIStrategy *getStrategy() const { return m_pStrategy; }
        virtual void setStrategy(AIStrategy *strategy) { m_pStrategy = strategy; }

        virtual void decreaseHpBy(int amount);


    protected:
        AIStrategy *m_pStrategy;
    };

}


#endif //LORAFEL_CHARACTERTILE_H
