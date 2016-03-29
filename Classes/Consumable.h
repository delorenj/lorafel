//
// Created by Jarad DeLorenzo on 3/28/16.
//

#ifndef LORAFEL_CONSUMABLE_H
#define LORAFEL_CONSUMABLE_H

#include "Item.h"
#include "Tile.h"

namespace lorafel {
    class Consumable : public Item {
    public:
        void use(Tile* pTarget);
    };
}

#endif //LORAFEL_CONSUMABLE_H
