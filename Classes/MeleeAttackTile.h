//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_MELEEATTACKTILE_H
#define LORAFEL_MELEEATTACKTILE_H

#include "Tile.h"

namespace lorafel {
    class MeleeAttackTile : public Tile {
    public:
        void onMatch(Match* pMatch) override;

        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("MeleeAttackTile");
            args["name"] = cocos2d::Value("Sword");
            args["tile_image"] = cocos2d::Value("sword.png");
            args["type"] = cocos2d::Value("melee");

            return init(args);
        }

        bool init(cocos2d::ValueMap args) override {
            return Tile::init(args);
        }

        static MeleeAttackTile *create(cocos2d::ValueMap args) {
            MeleeAttackTile * pRet = new(std::nothrow) MeleeAttackTile();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        CREATE_FUNC(MeleeAttackTile);
    };
}
#endif //LORAFEL_MELEEATTACKTILE_H
