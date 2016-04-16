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
        virtual bool init() override {
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

        CREATE_FUNC(MoneyBagTile)
    };
}
#endif //LORAFEL_MONEYBAGTILE_H
