//
// Created by Jarad DeLorenzo on 7/15/16.
//

#ifndef LORAFEL_IINVENTORYABLE_H
#define LORAFEL_IINVENTORYABLE_H

namespace lorafel {
    class IInventoryable {
    public:
        virtual bool addToInventory() = 0;
    };
}

#endif //LORAFEL_IINVENTORYABLE_H
