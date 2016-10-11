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

            initWithSpriteFrameName(getTileImage());

            m_baseAttack = 500;
			m_baseHitDistance = 1;
            addEquipMask(Player::LEFT_HAND);
            addEquipMask(Player::RIGHT_HAND);
            Item::setItemName(getItemName());

			std::function<void(void)>* customAttribute = new std::function<void(void)>([=]() {
				CCLOG("Thing! =D");
			});

			/**
			 * Now we build what stats are shown in
			 * the item detail window
			 */
			m_pItemStats = new std::set<ItemStat*>();
			m_pItemStats->insert(new ItemStat("Attack", to_string(getAttack())));
			m_pItemStats->insert(new ItemStat("Hit Distance", to_string(getHitDistance())));

			/**
			 * Here we add special Attribute stats
			 * that go in a different window section
			 */
			m_pItemAttributes = new std::set<ItemStat*>();
			m_pItemAttributes->insert(new ItemStat("10% Life Gained per Damage", customAttribute));
			m_pItemAttributes->insert(new ItemStat("Chance to poison for 2 turns", customAttribute));

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

		virtual int getNextLevelCost() override {
			switch(getLevel()) {
				case 1: return 100;
				case 2: return 4000;
				case 3:
				default: return 10000;
			};
		}

		virtual int getPrice() override {
			switch(getLevel()) {
				case 1: return 105;
				case 2: return 700;
				case 3:
				default: return 1250;
			};

		}

		int getRequiredPlayerLevel() override {
			switch(getLevel()) {
				case 1: return 5;
				case 2: return 9;
				case 3:
				default: return 12;
			};
		}

		std::string getTileImage() {
			return m_arguments["tile_image"].isNull() ?
					"lame-spider-sword.png" : m_arguments["tile_image"].asString();
		};

		std::string getItemName() {
			return m_arguments["item_name"].isNull() ?
					"Lame Spider Sword" : m_arguments["item_name"].asString();
		};

	};
}

#endif //LORAFEL_LAMESPIDERSWORDITEM_H
