//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_STICKMAN_H
#define LORAFEL_STICKMAN_H

#include "EnemyTile.h"
#include "RandomAIStrategy.h"
#include "XpStatResult.h"
#include "PoisonGlyph.h"
#include "StormGlyph.h"
#include "Level.h"

namespace lorafel {
    class StickMan : public EnemyTile {
    public:
        virtual bool init() override {
            if(!EnemyTile::init()) {
                return false;
            }
            if (initWithSpriteFrameName("enemy1.png"))
            {
                setTileName("Stick Man");
                initOptions();
                addEvents();
                addStatResult(new XpStatResult(200));
                setHp(100);
                setMaxHp(100);
                setStrategy(new RandomAIStrategy());

                m_pTileConfigs = new TileConfigs();
                auto config = new TileConfig();
                config->create = std::bind([=](){ return PoisonGlyph::create();});
                config->frequency = 5;
                m_pTileConfigs->push_back(config);

                config = new TileConfig();
                config->create = std::bind([=](){ return StormGlyph::create();});
                config->frequency = 5;
                m_pTileConfigs->push_back(config);

                return true;
            }

            return false;
        }
        CREATE_FUNC(StickMan);

//        virtual void applyHit(Match* pMatch) override;

    protected:
        /**
         * Overriding this so this enemy is easier. He will sometimes
         * drop normal tiles mixed in with the mean glyphs
         */
        Tile* getRandomGlyph() override {
            return CCRANDOM_0_1() < 0.5f ? m_pSwappyGrid->getLevel()->getRandomTile() : EnemyTile::getRandomGlyph();
        };
    };
}

#endif //LORAFEL_STICKMAN_H
