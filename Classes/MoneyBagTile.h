//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_MONEYBAGTILE_H
#define LORAFEL_MONEYBAGTILE_H

#include "Tile.h"

namespace lorafel {
    class MoneyBagTile : public Tile {
    public:
        MoneyBagTile();
        ~MoneyBagTile();

        static MoneyBagTile* create();
    };
}
#endif //LORAFEL_MONEYBAGTILE_H
