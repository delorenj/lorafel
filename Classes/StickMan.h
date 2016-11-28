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
        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("StickMan");
            args["name"] = cocos2d::Value("Stick Man");
            args["tile_image"] = cocos2d::Value("enemy1.png");
            args["type"] = cocos2d::Value("enemy");
            args["xp"] = cocos2d::Value(500);
            args["hp"] = cocos2d::Value(500);
            args["ai"] = cocos2d::Value("RandomAIStrategy");
            args["avatar_image"] = cocos2d::Value("stick_man_avatar.png");
            cocos2d::ValueVector glyphVec;
            cocos2d::ValueMap g1;
            g1["f"] = cocos2d::Value(5);
            g1["id"] = cocos2d::Value("poison");
            glyphVec.push_back(cocos2d::Value(g1));
            cocos2d::ValueMap g2;
            g2["f"] = cocos2d::Value(5);
            g2["id"] = cocos2d::Value("storm");
            glyphVec.push_back(cocos2d::Value(g2));
            args["glyphs"] = glyphVec;

            return init(args);
        }

        bool init(cocos2d::ValueMap args) override {
            if(!EnemyTile::init(args)) {
                return false;
            }
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

        static StickMan* create(cocos2d::ValueMap args) {
            StickMan *pRet = new(std::nothrow) StickMan();
            if (pRet && pRet->init(args))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
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
