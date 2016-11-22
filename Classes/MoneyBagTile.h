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
        virtual bool init(cocos2d::ValueMap args) override {
            if(!Tile::init()) {
                return false;
            }

            if (initWithSpriteFrameName("money_bag_1.png"))
            {
                setTileName("MoneyBag");
                initOptions();
                addEvents();
                addStatResult(new GoldStatResult(100));
                return true;
            }
            return false;

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
    };
}
#endif //LORAFEL_MONEYBAGTILE_H
