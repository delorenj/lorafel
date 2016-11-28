//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_CARROTTILE_H
#define LORAFEL_CARROTTILE_H

#include "Tile.h"
#include "XpStatResult.h"
#include "Globals.h"

namespace lorafel {
    class CarrotTile : public Tile {
    public:
        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("Tile");
            args["name"] = cocos2d::Value("Carrot");
            args["tile_image"] = cocos2d::Value("carrot.png");
            args["type"] = cocos2d::Value("generic");
            args["xp"] = cocos2d::Value(20);

            return init(args);
        }

        bool init(cocos2d::ValueMap args) override {
            return Tile::init(args);
        }

        CREATE_FUNC(CarrotTile);

        static CarrotTile *create(cocos2d::ValueMap args) {
            CarrotTile * pRet = new(std::nothrow) CarrotTile();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }    };
}

#endif //LORAFEL_CARROTTILE_H
