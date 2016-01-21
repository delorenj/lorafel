//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYER_H
#define LORAFEL_PLAYER_H

#include "Progress.h"
#include "Achievements.h"
#include "Inventory.h"
#include "LinearLevelManager.h"

namespace lorafel {
    class Player {

    public:
        Player();
        virtual ~Player();

        void initFromServer();

        LevelManager* getLevelManager() const { return m_pLevelManager; }

        unsigned long updateGoldBy(unsigned long val) {
            val = val > m_maxGold - m_gold ? m_maxGold : val;
            m_gold += val;
            return m_gold;
        }

        unsigned long getGold() const { return m_gold; }

        void setGold(unsigned long val) { m_gold = std::max(val, m_maxGold); }

        unsigned long updateHpBy(unsigned long val) {
            val = val > m_maxHp - m_hp ? m_maxHp : val;
            m_hp += val;
            return m_hp;
        }

        unsigned long getHp() const { return m_gold; }

        void setHp(unsigned long val) { m_hp = std::max(val, m_maxHp); }

        unsigned long updateMpBy(unsigned long val) {
            val = val > m_maxMp - m_mp ? m_maxMp : val;
            m_mp += val;
            return m_mp;
        }

        unsigned long getMp() const { return m_mp; }

        void setMp(unsigned long val) { m_mp = std::max(val, m_maxMp); }

    protected:
        // Current Stats
        unsigned long m_gold = 0;
        unsigned long m_hp = 100;
        unsigned long m_mp = 20;

        // Stat Ranges
        unsigned long m_maxGold = 5000;
        unsigned long m_maxHp = 100;
        unsigned long m_maxMp = 20;

        LinearLevelManager* m_pLevelManager;
        Progress*   m_pProgress;
        Achievements* m_pAchievements;
        Inventory* m_pInventory;

    };
}

#endif //LORAFEL_PLAYER_H
