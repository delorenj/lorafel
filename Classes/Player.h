//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYER_H
#define LORAFEL_PLAYER_H

#include "Progress.h"
#include "Achievements.h"
#include "Inventory.h"
#include "LinearXpManager.h"
#include "HeroTile.h"
#include "Consumable.h"
#include "Hook.h"
#include "EquipSerializer.h"
#include "InventorySlotSerializer.h"
#include "NonConsumable.h"
#include "EnemyTile.h"

namespace lorafel {
    class Player {
    public:
        static const int UNLOCK_CONSUMABLE_SLOT_2 = 15;
        static const int UNLOCK_CONSUMABLE_SLOT_3 = 40;
        static const int MAX_CONSUMABLE_SLOTS = 3;
        static const int HEAD               = 1;
        static const int LEFT_HAND          = 2;
        static const int RIGHT_HAND         = 3;
        static const int BODY               = 4;
        static const int FEET               = 5;
        static const int NECKLACE           = 6;
        static const int LEFT_RING          = 7;
        static const int RIGHT_RING         = 8;
        static const int ACTIONITEM         = 9;
        static const int CONSUMABLE         = 10;

        int getRandHit(EnemyTile *pEnemyTile);

        bool tileWithinHitDistance(Tile *pTile);

        void attack(EnemyTile *pTile);

    public:

        Player();
        virtual ~Player();
        void initFromServer();

        /**
         * Getters and Setters
        */
        const int getNumConsumableSlots() const;

        Consumable* getConsumableSlotItem(int i);
        void equipHook();
        XpManager* getXpManager() const { return m_pXpManager; }
        int updateGoldBy(int amount, Match* pMatch);
        int updateGoldBy(int amount, cocos2d::Vec2 floatiePos);
        int updateGoldBy(int amount);
        void setGold(unsigned int amount) { m_gold = amount; }
        void setXp(unsigned int amount) { m_pXpManager->setXp(amount); }
        int getGold() const { return m_gold; }
        int getMaxGold() const { return m_maxGold; }
        int getMaxHp() const { return m_maxHp; }
        int updateHpBy(int val);
        int getHp() const { return m_hp; }
        void setHp(int val) { m_hp = std::max(val, m_maxHp); }
        int updateMpBy(int val);
        int getMp() const { return m_mp; }
        int getMaxMp() const { return m_maxMp; }
        void setMp(int val) { m_mp = std::max(val, m_maxMp); }
        Tile* getTile() const;
        void setTile(Tile* tile) { m_pTile = tile; }
        Inventory* getInventory() const { return m_pInventory; }
        bool equipConsumableSlot(std::string itemId);
        bool equipConsumableSlot(std::string itemId, int slot);
        Hook* getHook() const { return m_pHook; }
        Item* getEquippedItemBySlotType(int equipMask) { return m_equipDictionary[equipMask]; }
        std::shared_ptr<InventorySlotSerializer> getInventorySlotSerializer() const { return m_pInventorySlotSerializer; }
        void equipItem(int slot, Item* pItem);
        bool isEquipped(Item* pItem);
        int getBaseAttack() const;
        int getBaseDefend() const;
        int getStr() const { return m_str; }
        int getDef() const { return m_def; }
        void setStr(int str) { m_str = str; }
        void setDef(int def) { m_def = def; }
        int getMaxMoveDistance() { return m_maxMoveDistance; }
        void setMaxMoveDistance(int moveDistance) { m_maxMoveDistance = moveDistance; }
        std::vector<NonConsumable*> getEquippedItems();

    protected:
        // Current Stats
        int m_gold = 0;
        int m_hp = 800;
        int m_mp = 3;
        int m_str = 10;
        int m_def = 10;

        // Stat Ranges
        int m_maxGold = 100000;
        int m_maxHp = 1000;
        int m_maxMp = 3;
        int m_maxMoveDistance = 2;

        cocos2d::EventDispatcher* m_pDispatcher;

        LinearXpManager* m_pXpManager;
        std::shared_ptr<EquipSerializer> m_pEquipSerializer;
        std::shared_ptr<InventorySlotSerializer> m_pInventorySlotSerializer;
        Progress*   m_pProgress;
        Achievements* m_pAchievements;
        Inventory* m_pInventory;
        std::map<int, Consumable*> m_activeConsumables;
        std::unordered_map<int, Item*> m_equipDictionary;
        Hook* m_pHook;

    protected:
        Tile* m_pTile;
    };

}

#endif //LORAFEL_PLAYER_H
