//
// Created by Jarad DeLorenzo on 6/9/16.
//

#ifndef LORAFEL_NONCONSUMABLE_H
#define LORAFEL_NONCONSUMABLE_H

#include "Item.h"

namespace lorafel {
    class NonConsumable : public Item {
    public:

        virtual bool init() override;
        virtual std::vector<int> getEquipMasks() = 0;
    };
}

#endif //LORAFEL_NONCONSUMABLE_H
