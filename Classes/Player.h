//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYER_H
#define LORAFEL_PLAYER_H

#include "Progress.h"
#include "Achievements.h"
#include "Inventory.h"
#include "LinearLevelManager.h"
#include "HeroTile.h"
#include "Consumable.h"
#include "Hook.h"

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

        Consumable* getConsumableSlotItem(int i);

        void equipHook();

    public:
        Player();
        virtual ~Player();

        void initFromServer();

        /**
         * Getters and Setters
        */
        const int getNumConsumableSlots() const;

        LevelManager* getLevelManager() const { return m_pLevelManager; }
        int updateGoldBy(int amount, Match* pMatch);
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
        bool equipConsumableSlot(const char* itemName);
        bool equipConsumableSlot(const char* itemName, int slot);
        Hook* getHook() const { return m_pHook; }

    protected:
        // Current Stats
        int m_gold = 0;
        int m_hp = 800;
        int m_mp = 3;

        // Stat Ranges
        int m_maxGold = 1000;
        int m_maxHp = 1000;
        int m_maxMp = 3;

        cocos2d::EventDispatcher* m_pDispatcher;

        LinearLevelManager* m_pLevelManager;
        Progress*   m_pProgress;
        Achievements* m_pAchievements;
        Inventory* m_pInventory;
        std::map<int, Consumable*> m_activeConsumables;
        Hook* m_pHook;

    protected:
        Tile* m_pTile;

    };

}

#endif //LORAFEL_PLAYER_H
