//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_LEVELMANAGER_H
#define LORAFEL_LEVELMANAGER_H

namespace lorafel {

    class LevelManager {
    public:
        LevelManager() : m_xp(1) { };
        LevelManager(unsigned long xp) : m_xp(xp) { };

        // Returns amount until next level
        virtual const unsigned long getLevelUpIn() const {
                return levelToXp(getLevel()+1) - m_xp;
        };

        // Returns amount until next level
        virtual const int getLevelUpInPercent() const = 0;

        // Calculates and returns the current level
        virtual const unsigned long getLevel() const {
                return xpToLevel(m_xp);
        }

        // Returns the current XP
        virtual const unsigned long getXp() const  { return m_xp; }

        // Increase the current XP amount by 'xp'
        virtual const unsigned long incrementXpBy(const unsigned long xp) {
                cocos2d::Event::
                m_xp += xp;
        }

        // Converts xp to level
        virtual const unsigned long xpToLevel(const unsigned long xp) const = 0;

        // Converts level to xp
        virtual const unsigned long levelToXp(const unsigned long level) const = 0;

    protected:
        unsigned long m_xp;
    };

}
#endif //LORAFEL_LEVELMANAGER_H
