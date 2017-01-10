//
// Created by Jarad M DeLorenzo on 1/10/17.
//

#ifndef LORAFEL_INVENTORYSTATSBAR_H
#define LORAFEL_INVENTORYSTATSBAR_H

#include "Globals.h"
#include "cocos2d.h"

USING_NS_CC;

class InventoryStatsBar : public cocos2d::Sprite {
public:

    bool init(cocos2d::Node* container);
    static InventoryStatsBar* create(cocos2d::Node* container)
    {
        InventoryStatsBar *pRet = new(std::nothrow) InventoryStatsBar();
        if (pRet && pRet->init(container))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }

};


#endif //LORAFEL_INVENTORYSTATSBAR_H
