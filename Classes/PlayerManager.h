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

				ValueVector itemVec = valueMap["items"].asValueVector();
				for(auto itemVal : itemVec) {
					ValueMap itemValMap = itemVal.asValueMap();
					std::string itemClass = itemValMap["class"].asString();
					cocos2d::ValueVector itemArgs = itemValMap["arguments"].asValueVector();
					int itemQuantity = itemValMap["quantity"].asInt();
					CCLOG(" - loading %d of item %s", itemQuantity, itemClass.c_str());
					for(int i=0; i<itemQuantity; i++) {
						Item* pItem = ItemFactory::getInstance()->createItem(itemClass, itemArgs);
						pInventory->addItem(pItem);
					}
				}
			}

//            m_pPlayer->equipConsumableSlot("Yummy Potion", 0);
            return m_pPlayer;
        }

        Player* getPlayer() const { return m_pPlayer; }

    protected:
        static PlayerManager *_instance;
        Player* m_pPlayer;

    };
}



#endif //LORAFEL_PLAYERMANAGER_H
