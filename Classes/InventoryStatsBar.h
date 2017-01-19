//
// Created by Jarad M DeLorenzo on 1/10/17.
//

#ifndef LORAFEL_INVENTORYSTATSBAR_H
#define LORAFEL_INVENTORYSTATSBAR_H

#include "Globals.h"
#include "cocos2d.h"

USING_NS_CC;

namespace lorafel {
    class InventoryStatsBar : public cocos2d::Node {
    public:

        bool init(cocos2d::Node *container);

        static InventoryStatsBar *create(cocos2d::Node *container) {
            InventoryStatsBar *pRet = new(std::nothrow) InventoryStatsBar();
            if (pRet && pRet->init(container)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        void setStat(const std::string stat, int val);

    protected:
        cocos2d::Label* m_pStr;
        cocos2d::Label* m_pInt;
        cocos2d::Label* m_pDef;
        cocos2d::Label* m_pDex;
        cocos2d::Label* m_pMov;

        cocos2d::Label* m_pStrVal;
        cocos2d::Label* m_pIntVal;
        cocos2d::Label* m_pDefVal;
        cocos2d::Label* m_pDexVal;
        cocos2d::Label* m_pMovVal;

        void createStatLabel(cocos2d::Label *statNameLabel, cocos2d::Label *statValLabel, const std::string statName, int val, float xPosPercent);
    };
}

#endif //LORAFEL_INVENTORYSTATSBAR_H
