//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_XPMANAGER_H
#define LORAFEL_XPMANAGER_H

#include "EventDataInteger.h"
#include "EventDataFloatie.h"
#include "Match.h"
#include "FirebaseDatabase.h"

namespace lorafel {
    class XpManager {
    public:
        virtual ~XpManager() { };
        
        XpManager(unsigned long xp) : m_xp(xp) {
                m_pDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
        };

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
        virtual void setXp(unsigned int amount) { m_xp = amount; }
        
        // Increase the current XP amount by 'xp'
        virtual const unsigned long incrementXpBy(int xp, Match *pMatch) {
            // If XP was enough to level player
            // then fire off a levelup event
            if(xp >= getLevelUpIn()) {
                cocos2d::EventCustom levelEvent("levelup");
                EventData* levelVal = new EventDataInteger((int) (getLevel()+1));
                levelEvent.setUserData(levelVal);
                m_pDispatcher->dispatchEvent(&levelEvent);
                CC_SAFE_DELETE(levelVal);
            }
            
            // Increment player xp
            m_xp += xp;
            FirebaseDatabase::getInstance()->setXP(m_xp);

            // Fire off an XP event
            cocos2d::EventCustom e("xp");
            EventData* val = new EventDataFloatie(xp, pMatch->getTileSetCenter());
            e.setUserData(val);
            m_pDispatcher->dispatchEvent(&e);
            CC_SAFE_DELETE(val);
            return m_xp;
        }

        // Converts xp to level
        virtual const unsigned long xpToLevel(const unsigned long xp) const = 0;

        // Converts level to xp
        virtual const unsigned long levelToXp(const unsigned long level) const = 0;

    protected:
        unsigned long m_xp;
        cocos2d::EventDispatcher* m_pDispatcher;
    };

}
#endif //LORAFEL_XPMANAGER_H
