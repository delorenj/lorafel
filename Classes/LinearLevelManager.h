//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_LINEARLEVELMANAGER_H
#define LORAFEL_LINEARLEVELMANAGER_H

#include "LevelManager.h"

namespace lorafel {

    class LinearLevelManager : public LevelManager {
    public:
        LinearLevelManager() : LevelManager(0) {} ;
        LinearLevelManager(unsigned long xp) : LevelManager(xp) {} ;

        // Converts xp to level
        virtual const unsigned long xpToLevel(const unsigned long xp) const override {
            return (const unsigned long)std::floor((std::sqrt(100 * (2 * xp +25))+50)/100);
        }

        // Converts level to xp
        virtual const unsigned long levelToXp(const unsigned long level) const override {
            return (std::pow(level, 2)+level)/2*100-(level*100);
        }

        virtual const int getLevelUpInPercent() const override {
            auto val = (std::sqrt(100 * (2 * m_xp +25))+50)/100;
            auto pc = (val - std::floor(val)) * 100;
            return pc;
        }
    };
}

#endif //LORAFEL_LINEARLEVELMANAGER_H
