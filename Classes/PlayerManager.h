//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYERMANAGER_H
#define LORAFEL_PLAYERMANAGER_H

#include <string>
#include "Player.h"
#include "HealthPotion.h"
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
                for(auto v : valueMap) {
                    CCLOG("PlayerManager::loadPlayer() - VMAP Values: %s", v.first.c_str());
                }
                loadStats(valueMap);
				loadInventory(valueMap);
                loadEquipSlots(valueMap);
                loadProgress(valueMap);
			}

            return m_pPlayer;
        }

        void resetPlayerStats() {
            getPlayer()->setHp(getPlayer()->getMaxHp());
            getPlayer()->setMp(getPlayer()->getMaxMp());
        }

        void loadStats(ValueMap &valueMap) {
            CCLOG("PlayerManager::loadStats() - Enter");
            if(!valueMap["gold"].isNull()) {
                CCLOG("PlayerManager::loadStats() - Got Gold");
                getPlayer()->setGold(valueMap["gold"].asUnsignedInt());
            } else {
                getPlayer()->setGold(0);
            }
            if(!valueMap["xp"].isNull()) {
                getPlayer()->setXp(valueMap["xp"].asUnsignedInt());
                CCLOG("PlayerManager::loadStats() - Got Xp");
            } else {
                getPlayer()->setXp(0);
            }
            if(!valueMap["str"].isNull()) {
                getPlayer()->setStr(valueMap["str"].asUnsignedInt());
                CCLOG("PlayerManager::loadStats() - Got str");
            } else {
                getPlayer()->setStr(0);
            }
            if(!valueMap["def"].isNull()) {
                getPlayer()->setDef(valueMap["def"].asUnsignedInt());
                CCLOG("PlayerManager::loadStats() - Got def");
            } else {
                getPlayer()->setDef(0);
            }
            if(!valueMap["max_hp"].isNull()) {
                getPlayer()->setMaxHp(valueMap["max_hp"].asUnsignedInt());
                CCLOG("PlayerManager::loadStats() - Got max_hp");
            } else {
                getPlayer()->setMaxHp(1000);
            }
            if(!valueMap["max_mp"].isNull()) {
                getPlayer()->setMaxMp(valueMap["max_mp"].asUnsignedInt());
                CCLOG("PlayerManager::loadStats() - Got max_mp");
            } else {
                getPlayer()->setMaxMp(3);
            }
            if(!valueMap["max_move_distance"].isNull()) {
                getPlayer()->setMaxMoveDistance(valueMap["max_move_distance"].asInt());
                CCLOG("PlayerManager::loadStats() - Got max_move_distance");
            }

            /**
             * Always load player with 100% of health and magic
             */
            resetPlayerStats();
        }
        
        void loadEquipSlots(ValueMap &valueMap) const {
            CCLOG("PlayerManager::loadEquipSlots() - Enter");
            Inventory* pInventory = m_pPlayer->getInventory();
            
            if(valueMap["equip_slots"].isNull()) {
                return;
            }
            
            ValueMap equipSlots = valueMap["equip_slots"].asValueMap();
            for(auto equipSlot : equipSlots) {
                std::string s = equipSlot.first;
                s = s.substr(0, s.size()-1);
                int slotId = parseInt(s);
                std::string itemId = equipSlot.second.asString();
                Item* pItem = pInventory->getItem(itemId);
                if(pItem != nullptr) {
                    CCLOG(" - equipping slot %d with item id %s", slotId, pItem->getItemName().c_str());
                    getPlayer()->equipItem(slotId, pItem);
                } else {
                    CCLOG("PlayerManager::loadEquipSlots() - Tried to equip slot %d with item id %s, but failed", slotId, itemId.c_str());
                }
            }
        }
        
		void loadInventory(ValueMap &valueMap) {
            CCLOG("PlayerManager::loadInventory() - Enter");
			Inventory* pInventory = m_pPlayer->getInventory();
            /**
             * If items is null, then only a single item is being
             * passed in. This happens when an item is dynamically
             * added through the database. The database will detect
             * the new item and call this function.
             *
             * Items is NOT null when loading the game explicitly
             * from the database. In this case, we need to loop
             * through each item entry and create the item object
             */
            // TODO: Refactor ?
            if(valueMap["items"].isNull()) {
				return;
                std::string itemId = valueMap["id"].asString();
                std::string oldId = valueMap["oldId"].asString();
                std::string newId = valueMap["newId"].asString();
                Item* pItem = createItemFromDatabaseEntry(newId, valueMap);

                int itemQuantity = 1;
                if(!valueMap["quantity"].isNull() && valueMap["quantity"].getType() == Value::Type::INTEGER) {
                    itemQuantity = valueMap["quantity"].asInt();
                }

                pInventory->addItem(pItem, itemQuantity);

            } else {
                ValueMap itemVec = valueMap["items"].asValueMap();
                for(auto itemVal : itemVec) {
                    auto itemId = itemVal.first;
                    ValueMap itemValMap = itemVal.second.asValueMap();
                    Item* pItem = createItemFromDatabaseEntry(itemId, itemValMap);
                    
                    int itemQuantity = 1;
                    if(!itemValMap["quantity"].isNull() && itemValMap["quantity"].getType() == Value::Type::INTEGER) {
                        itemQuantity = itemValMap["quantity"].asInt();
                    }
                    
                    pInventory->addItem(pItem, itemQuantity);
                }
            }
        }
        
        Item* createItemFromDatabaseEntry(std::string itemId, ValueMap &itemValMap) {

            /**
             * If any args passed in, set them here
             * or set null
             */
            ValueMap itemArgs;
            if(!itemValMap["arguments"].isNull() && itemValMap["arguments"].getType() == Value::Type::MAP) {
                itemArgs = itemValMap["arguments"].asValueMap();
            } else {
                return nullptr;
            }

            std::string itemClass = itemArgs["item_class"].asString();

            /**
             * If a quantity was passed in, set it here
             * otherwise set quantity to 1
             */
            int itemQuantity = 1;
            if(!itemValMap["quantity"].isNull() && itemValMap["quantity"].getType() == Value::Type::INTEGER) {
                itemQuantity = itemValMap["quantity"].asInt();
            }
            
            CCLOG("PlayerManager::loadInventory() - loading %d of item %s", itemQuantity, itemArgs["item_name"].asString().c_str());
            return ItemFactory::getInstance()->createItem(itemArgs, itemId);
        }


        void loadProgress(cocos2d::ValueMap data) {
            m_pPlayer->getProgress()->onLoadComplete(data);
        }

        Player* getPlayer() const { return m_pPlayer; }

    protected:
        static PlayerManager *_instance;
        Player* m_pPlayer;

    };
}



#endif //LORAFEL_PLAYERMANAGER_H
