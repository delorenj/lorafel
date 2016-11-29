//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_MONEYBAGTILE_H
#define LORAFEL_MONEYBAGTILE_H

#include "Tile.h"
#include "GoldStatResult.h"
#include "Globals.h"

namespace lorafel {
    class MoneyBagTile : public Tile {
    public:
        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("MoneyBagTile");
            args["name"] = cocos2d::Value("Money");
            args["tile_image"] = cocos2d::Value("money_bag_1.png");
            args["type"] = cocos2d::Value("money");

            return init(args);
        }
        virtual bool init(cocos2d::ValueMap args) override {
            if(!Tile::init(args)) {
                return false;
            }

            addStatResult(new GoldStatResult(100));

            return true;
        }

        static MoneyBagTile *create(cocos2d::ValueMap args) {
            MoneyBagTile * pRet = new(std::nothrow) MoneyBagTile();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        CREATE_FUNC(MoneyBagTile);
    };
}
#endif //LORAFEL_MONEYBAGTILE_H
