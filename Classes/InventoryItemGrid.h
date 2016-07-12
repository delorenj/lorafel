//
// Created by Jarad DeLorenzo on 7/9/16.
//

#ifndef LORAFEL_INVENTORYITEMGRID_H
#define LORAFEL_INVENTORYITEMGRID_H

#include "cocos2d.h"
#include "Grid.h"
#include "InventoryItemSlot.h"

USING_NS_CC;

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
        void loadInventory();

    protected:
        Grid<InventoryItemSlot*>* m_pGrid;


        Item* assignItemToSlot(Item* pItem);

        bool isEmpty(std::pair<int, int> pair);
    };
}

#endif //LORAFEL_INVENTORYITEMGRID_H
