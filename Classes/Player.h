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

namespace lorafel {
    class Player {

    public:
        Player();
        virtual ~Player();

        void initFromServer();
        LevelManager* getLevelManager() const { return m_pLevelManager; }
        int updateGoldBy(int amount, Match* pMatch);
        int getGold() const { return m_gold; }
        int getMaxGold() const { return m_maxGold; }
        unsigned long getMaxHp() const { return m_maxHp; }
        unsigned long updateHpBy(long val);
        unsigned long getHp() const { return m_hp; }
        void setHp(unsigned long val) { m_hp = std::max(val, m_maxHp); }
        unsigned long updateMpBy(unsigned long val);
        unsigned long getMp() const { return m_mp; }
        void setMp(unsigned long val) { m_mp = std::max(val, m_maxMp); }
        Tile* getTile() const;
        void setTile(Tile* tile) { m_pTile = tile; }

    protected:
        // Current Stats
        int m_gold = 0;
        unsigned long m_hp = 10000;
        unsigned long m_mp = 20;

        // Stat Ranges
        int m_maxGold = 1000;
        unsigned long m_maxHp = 10000;
        unsigned long m_maxMp = 20;

        cocos2d::EventDispatcher* m_pDispatcher;

        LinearLevelManager* m_pLevelManager;
        Progress*   m_pProgress;
        Achievements* m_pAchievements;
        Inventory* m_pInventory;

    protected:
        Tile* m_pTile;

    };

}

#endif //LORAFEL_PLAYER_H
