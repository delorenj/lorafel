//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_AVOCADOTILE_H
#define LORAFEL_AVOCADOTILE_H

#include "Tile.h"
#include "Globals.h"
#include "XpStatResult.h"

namespace lorafel {
    class AvocadoTile : public Tile {
    public:
        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("Tile");
            args["name"] = cocos2d::Value("Avocado");
            args["tile_image"] = cocos2d::Value("avocado.png");
            args["type"] = cocos2d::Value("generic");
            args["xp"] = cocos2d::Value(50);

            return init(args);
        }
        bool init(cocos2d::ValueMap args) override {
            return Tile::init(args);
        }

        CREATE_FUNC(AvocadoTile);

        static AvocadoTile *create(cocos2d::ValueMap args) {
            AvocadoTile * pRet = new(std::nothrow) AvocadoTile();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }
    };
}

#endif //LORAFEL_AVOCADOTILE_H
