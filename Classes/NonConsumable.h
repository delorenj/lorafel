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
        void setEquipMask(int mask) { m_equipMask = mask; }
        int getEquipMask() { return m_equipMask; }

    protected:
        int m_equipMask;
    };
}

#endif //LORAFEL_NONCONSUMABLE_H
