//
// Created by Jarad DeLorenzo on 6/9/16.
//

#ifndef LORAFEL_LAMESPIDERSWORDITEM_H
#define LORAFEL_LAMESPIDERSWORDITEM_H


#include "Weapon.h"
#include "Player.h"
#include "ISellable.h"
#include "IUpgradable.h"
#include "ItemAttribute.h"

namespace lorafel {
    class LameSpiderSword : public Weapon, public ISellable, public IUpgradable{
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

			std::function customAttribute = [=]() {
				CCLOG("Thing! =D");
			};

			/**
			 * Now we build what stats are shown in
			 * the item detail window
			 */
			m_pItemStats = new std::set<ItemStat*>();
			m_pItemStats->insert(new ItemStat("Attack", to_string(getAttack())));
			m_pItemStats->insert(new ItemStat("Hit Distance", to_string(getHitDistance())));
			m_pItemStats->insert(new ItemAttribute("10% Life Gained per Damage", customAttribute));

            return true;
        }

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

		virtual int getNextLevelCost() const override {
			return 100;
		}

		virtual int getPrice() const override {
			return 105;
		}

		virtual int getLevel() const override {
			return 1;
		}

	};
}

#endif //LORAFEL_LAMESPIDERSWORDITEM_H
