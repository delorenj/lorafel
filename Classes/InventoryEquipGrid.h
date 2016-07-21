//
// Created by Jarad DeLorenzo on 7/20/16.
//

#ifndef LORAFEL_INVENTORYEQUIPGRID_H
#define LORAFEL_INVENTORYEQUIPGRID_H

#include "Grid.h"
#include "Item.h"
#include "InventoryItemSlot.h"

namespace lorafel {
    class InventoryEquipGrid : public cocos2d::Sprite {
    public:

        bool init(cocos2d::Node* container);
        static InventoryEquipGrid* create(cocos2d::Node* container)
        {
            InventoryEquipGrid *pRet = new(std::nothrow) InventoryEquipGrid();
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
        InventoryItemSlot* m_pItemSlotBody;
        InventoryItemSlot* m_pItemSlotHead;
        InventoryItemSlot* m_pItemSlotLH;
        InventoryItemSlot* m_pItemSlotRH;
        InventoryItemSlot* m_pItemSlotFeet;
        InventoryItemSlot* m_pItemSlotLRing;
        InventoryItemSlot* m_pItemSlotRRing;
        InventoryItemSlot* m_pItemSlotNecklace;
        InventoryItemSlot* m_pItemSlotAction;
        InventoryItemSlot* m_pItemSlotConsumable;
    };
}

#endif //LORAFEL_INVENTORYEQUIPGRID_H
