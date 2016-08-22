//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYERMANAGER_H
#define LORAFEL_PLAYERMANAGER_H

#include <string>
#include "Player.h"
#include "HealthPotion.h"
#include "LameSpiderSword.h"
#include "DumbKnife.h"
#include "ItemFactory.h"

namespace lorafel {

    class PlayerManager {
    public:
        static PlayerManager *getInstance() {
            if (_instance == nullptr) {
                _instance = new PlayerManager();
            }
            return _instance;
        }

        Player* loadPlayer(cocos2d::Value data) {
			if(m_pPlayer != nullptr) {
				delete m_pPlayer;
				m_pPlayer = nullptr;
			}
			// For now, just make a default player
			// upon each load
			m_pPlayer = new Player();
			auto pInventory =m_pPlayer->getInventory();

			//TODO: Load player avatar image from database
			m_pPlayer->setTile(HeroTile::create("player.png"));

			if (!data.isNull() && data.getType() == Value::Type::MAP) {
				ValueMap valueMap = data.asValueMap();

				loadInventory(valueMap);
			}

//            m_pPlayer->equipConsumableSlot("Yummy Potion", 0);
            return m_pPlayer;
        }

		void loadInventory(ValueMap &valueMap) const {
			Inventory* pInventory = m_pPlayer->getInventory();
			ValueMap itemVec = valueMap["items"].asValueMap();
			for(auto itemVal : itemVec) {
					ValueMap itemValMap = itemVal.second.asValueMap();
					std::__1::string itemClass = itemValMap["class"].asString();
					/**
					 * If any args passed in, set them here
					 * or set null
					 */
					ValueVector itemArgs;
					if(!itemValMap["arguments"].isNull() && itemValMap["arguments"].getType() == Value::Type::VECTOR) {
						itemArgs = itemValMap["arguments"].asValueVector();
					} else {
						itemArgs = ValueVectorNull;
					}

					/**
					 * If a quantity was passed in, set it here
					 * otherwise set quantity to 1
					 */
					int itemQuantity = 1;
					if(!itemValMap["quantity"].isNull() && itemValMap["quantity"].getType() == Value::Type::INTEGER) {
						itemQuantity = itemValMap["quantity"].asInt();
					}

					CCLOG(" - loading %d of item %s", itemQuantity, itemClass.c_str());
					for(int i=0; i<itemQuantity; i++) {
						Item* pItem = ItemFactory::getInstance()->createItem(itemClass, itemArgs);
						pInventory->addItem(pItem);
					}
				}
		}

		Player* getPlayer() const { return m_pPlayer; }

    protected:
        static PlayerManager *_instance;
        Player* m_pPlayer;

    };
}



#endif //LORAFEL_PLAYERMANAGER_H
