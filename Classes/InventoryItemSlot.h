//
// Created by Jarad DeLorenzo on 7/10/16.
//

#ifndef LORAFEL_INVENTORYITEMSLOT_H
#define LORAFEL_INVENTORYITEMSLOT_H

#include "cocos2d.h"
#include "Item.h"
#include "Globals.h"
#include "InventoryItemGrid.h"
#include "ItemSlot.h"

USING_NS_CC;

namespace lorafel {
    class InventoryItemSlot : public ItemSlot {
    public:
        bool init(InventoryItemGrid* pGrid);

        static InventoryItemSlot* create(InventoryItemGrid* pGrid)
        {
            InventoryItemSlot *pRet = new(std::nothrow) InventoryItemSlot();
            if (pRet && pRet->init(pGrid))
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


        void update(float delta) override;
        std::pair<int, int> getCoords() const { return m_coords; }
        void setCoords(std::pair<int, int> coords) { m_coords = coords; }

        virtual void setItem(Item* pItem, int stackSize = 1) override;

    protected:
        InventoryItemGrid* m_pGrid;
        std::pair<int, int> m_coords;
        void addEvents();

    };
}

#endif //LORAFEL_INVENTORYITEMSLOT_H
