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
            CCLOG("PlayerManager::loadPlayer() - Enter");
			if(m_pPlayer != nullptr) {
				delete m_pPlayer;
				m_pPlayer = nullptr;
			}
			// For now, just make a default player
			// upon each load
			m_pPlayer = new Player();

			//TODO: Load player avatar image from database
			m_pPlayer->setTile(HeroTile::create("player.png"));

			if (!data.isNull() && data.getType() == Value::Type::MAP) {
                CCLOG("PlayerManager::loadPlayer() - Database data is valid. About to load player into memory...");
				ValueMap valueMap = data.asValueMap();

                loadStats(valueMap);
				loadInventory(valueMap);
                loadEquipSlots(valueMap);
			}

//            m_pPlayer->equipConsumableSlot("Yummy Potion", 0);
            return m_pPlayer;
        }

        void loadStats(ValueMap &valueMap) const {
            CCLOG("PlayerManager::loadStats() - Enter");
            if(!valueMap["gold"].isNull()) {
                getPlayer()->setGold(valueMap["gold"].asUnsignedInt());
            } else {
                getPlayer()->setGold(0);
            }
            if(!valueMap["xp"].isNull()) {
                getPlayer()->setXp(valueMap["xp"].asUnsignedInt());
            } else {
                getPlayer()->setXp(0);
            }
        }
        
        void loadEquipSlots(ValueMap &valueMap) const {
            CCLOG("PlayerManager::loadEquipSlots() - Enter");
            Inventory* pInventory = m_pPlayer->getInventory();
            
            if(valueMap["equip_slots"].isNull() || valueMap["equip_slots"].getType() != Value::Type::MAP) {
                return;
            }
            
            ValueMap equipSlots = valueMap["equip_slots"].asValueMap();
            for(auto equipSlot : equipSlots) {
                int slotId = parseInt(equipSlot.first);
                std::string itemId = equipSlot.second.asString();
                Item* pItem = pInventory->getItem(itemId);
                CCLOG(" - equipping slot %d with item id %s", slotId, pItem->getItemName().c_str());
                getPlayer()->equipItem(slotId, pItem);
            }
        }
        
		void loadInventory(ValueMap &valueMap) const {
            CCLOG("PlayerManager::loadInventory() - Enter");
			Inventory* pInventory = m_pPlayer->getInventory();
			ValueMap itemVec = valueMap["items"].asValueMap();
			for(auto itemVal : itemVec) {
                    auto itemId = itemVal.first;
					ValueMap itemValMap = itemVal.second.asValueMap();
					std::string itemClass = itemValMap["class"].asString();
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
						Item* pItem = ItemFactory::getInstance()->createItem(itemClass, itemArgs, itemId);
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
