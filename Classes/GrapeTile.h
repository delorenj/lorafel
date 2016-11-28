//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_GRAPETILE_H
#define LORAFEL_GRAPETILE_H

#include "Tile.h"
#include "Globals.h"
#include "XpStatResult.h"

namespace lorafel {
    class GrapeTile : public Tile {
    public:
        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("Tile");
            args["name"] = cocos2d::Value("Grapes");
            args["tile_image"] = cocos2d::Value("grapes.png");
            args["type"] = cocos2d::Value("generic");
            args["xp"] = cocos2d::Value(10);

            return init(args);
        }

        bool init(cocos2d::ValueMap args) override {
            return Tile::init(args);
        }

        CREATE_FUNC(GrapeTile);

        static GrapeTile* create(cocos2d::ValueMap args) {
            GrapeTile * pRet = new(std::nothrow) GrapeTile();
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

#endif //LORAFEL_GRAPETILE_H
