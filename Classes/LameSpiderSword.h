//
// Created by Jarad DeLorenzo on 6/9/16.
//

#ifndef LORAFEL_LAMESPIDERSWORDITEM_H
#define LORAFEL_LAMESPIDERSWORDITEM_H


#include "Weapon.h"
#include "Player.h"

namespace lorafel {
    class LameSpiderSword : public Weapon {
    public:
        virtual bool init() override {
            if(!Weapon::init()) {
                return false;
            }

            initWithSpriteFrameName("lame-spider-sword.png");
            m_damage = 500;
            addEquipMask(Player::LEFT_HAND);
            addEquipMask(Player::RIGHT_HAND);
            setItemName("Lame Spider Sword");
            return true;
        }

        CREATE_FUNC(LameSpiderSword);

    };
}

#endif //LORAFEL_LAMESPIDERSWORDITEM_H
