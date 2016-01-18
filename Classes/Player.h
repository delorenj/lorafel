//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYER_H
#define LORAFEL_PLAYER_H

#include "Progress.h"
#include "Achievements.h"
#include "Inventory.h"
#include "ExponentialLevelManager.h"

namespace lorafel {
    class Player {

    public:
        Player();
        virtual ~Player();

        void initFromServer();

    protected:
        // Current Stats
        unsigned long m_xp = 0;
        unsigned long m_gold = 0;

        // Stat Ranges
        unsigned long m_maxHp = 100;
        unsigned long m_maxMp = 20;

        ExponentialLevelManager* m_pLevelManager;
        Progress*   m_pProgress;
        Achievements* m_pAchievements;
        Inventory* m_pInventory;

    };
}

#endif //LORAFEL_PLAYER_H
