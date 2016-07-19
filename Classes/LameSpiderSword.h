//
// Created by Jarad DeLorenzo on 6/9/16.
//

#ifndef LORAFEL_LAMESPIDERSWORDITEM_H
#define LORAFEL_LAMESPIDERSWORDITEM_H


#include "Weapon.h"

namespace lorafel {
    class LameSpiderSword : public Weapon {
    public:
        virtual bool init() override {
            if(!Weapon::init()) {
                return false;
            }

            initWithSpriteFrameName("lame-spider-sword.png");
            m_damage = 500;
            m_equipMask = Player::LEFT_HAND | Player::RIGHT_HAND;
            return true;
        }

        CREATE_FUNC(LameSpiderSword);

        virtual const char* getItemName() const override { return m_itemName; }


    protected:
        const char* m_itemName = "Lame Spider Sword";


    };
}

#endif //LORAFEL_LAMESPIDERSWORDITEM_H
