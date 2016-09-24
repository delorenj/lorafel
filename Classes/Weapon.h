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

        virtual int getAttack() {
            return m_arguments["attack"].isNull() ?
                    m_baseAttack : m_baseAttack + m_arguments["attack"].asInt();
        }

        virtual int getHitDistance() {
            return m_arguments["hit_distance"].isNull() ?
                    m_baseHitDistance : m_baseHitDistance + m_arguments["hit_distance"].asInt();
        }

    protected:
        int m_baseAttack;
        int m_baseHitDistance;
    };
}

#endif //LORAFEL_WEAPON_H
