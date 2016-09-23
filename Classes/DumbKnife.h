//
// Created by Jarad DeLorenzo on 7/29/16.
//

#ifndef LORAFEL_DUMBKNIFE_H
#define LORAFEL_DUMBKNIFE_H

#include "Player.h"

namespace lorafel {
    class DumbKnife : public Weapon, public ISellable {
    public:
        virtual bool init() override {
            if(!Weapon::init()) {
                return false;
            }
            m_className = "DumbKnife";
            setArguments(ValueVectorNull);
            initWithSpriteFrameName("dumb-knife.png");
            m_damage = 100;
            addEquipMask(Player::LEFT_HAND);
            addEquipMask(Player::RIGHT_HAND);
            setItemName("Dumb Knife");
            return true;
        }

        virtual int getPrice() const override {
            return 5;
        }

        CREATE_FUNC(DumbKnife);

    };
}

#endif //LORAFEL_DUMBKNIFE_H
