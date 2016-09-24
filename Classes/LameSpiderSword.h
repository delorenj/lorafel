//
// Created by Jarad DeLorenzo on 6/9/16.
//

#ifndef LORAFEL_LAMESPIDERSWORDITEM_H
#define LORAFEL_LAMESPIDERSWORDITEM_H


#include "Weapon.h"
#include "Player.h"
#include "ISellable.h"

namespace lorafel {
    class LameSpiderSword : public Weapon, public ISellable {
    public:
        virtual bool init(ValueMap args) {
            if(!Weapon::init()) {
                return false;
            }
            m_className = "LameSpiderSword";
            setArguments(args);
            initWithSpriteFrameName("lame-spider-sword.png");
            m_baseAttack = 500;
			m_baseHitDistance = 1;
            addEquipMask(Player::LEFT_HAND);
            addEquipMask(Player::RIGHT_HAND);
            setItemName("Lame Spider Sword");

			/**
			 * Now we build what stats are shown in
			 * the item detail window
			 */
			m_pItemStats = new std::set<ItemStat*>();
			m_pItemStats->insert(new ItemStat("Attack", to_string(getAttack())));
			m_pItemStats->insert(new ItemStat("Hit Distance", to_string(getHitDistance())));

            return true;
        }

		virtual int getPrice() const override { return 105; }

		static LameSpiderSword* create(ValueMap args) {
			LameSpiderSword* pRet = new(std::nothrow) LameSpiderSword();
			if (pRet && pRet->init(args)) {
				pRet->autorelease();
				return pRet;
			} else {
				delete pRet;
				pRet = nullptr;
				return nullptr;
			}
		}


	};
}

#endif //LORAFEL_LAMESPIDERSWORDITEM_H
