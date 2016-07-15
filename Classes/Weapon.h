//
// Created by Jarad DeLorenzo on 6/9/16.
//

#ifndef LORAFEL_WEAPON_H
#define LORAFEL_WEAPON_H

#include "NonConsumable.h"

namespace lorafel {
    class Weapon : public NonConsumable {
    public:
        virtual bool init() override;
        virtual bool addToInventory() override;

    protected:
        int m_damage;
    };
}

#endif //LORAFEL_WEAPON_H
