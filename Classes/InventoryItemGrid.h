//
// Created by Jarad DeLorenzo on 7/9/16.
//

#ifndef LORAFEL_INVENTORYITEMGRID_H
#define LORAFEL_INVENTORYITEMGRID_H

#include "cocos2d.h"

namespace lorafel {
    class InventoryItemGrid : public cocos2d::Sprite {
    public:
        static const int NUM_ROWS = 4;
        static const int NUM_COLS = 8;

        bool init(cocos2d::Node* container);
        static InventoryItemGrid* create(cocos2d::Node* container)
        {
            InventoryItemGrid *pRet = new(std::nothrow) InventoryItemGrid();
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

    protected:
        float distribute(int idx, int total, float size) const;
    };
}

#endif //LORAFEL_INVENTORYITEMGRID_H
