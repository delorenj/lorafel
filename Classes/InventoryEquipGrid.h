//
// Created by Jarad DeLorenzo on 7/20/16.
//

#ifndef LORAFEL_INVENTORYEQUIPGRID_H
#define LORAFEL_INVENTORYEQUIPGRID_H

#include "cocos2d.h"
#include "Item.h"
#include "EquipItemSlot.h"

USING_NS_CC;

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

        EquipItemSlot* getSlotFromPosition(const Vec2& pos);
        void loadInventory();

        bool isInitialized() const { return m_initialized; }

	protected:
        std::vector<EquipItemSlot*> m_equipSlots;
        EquipItemSlot* m_pItemSlotBody;
        EquipItemSlot* m_pItemSlotHead;
        EquipItemSlot* m_pItemSlotLH;
        EquipItemSlot* m_pItemSlotRH;
        EquipItemSlot* m_pItemSlotFeet;
        EquipItemSlot* m_pItemSlotLRing;
        EquipItemSlot* m_pItemSlotRRing;
        EquipItemSlot* m_pItemSlotNecklace;
        EquipItemSlot* m_pItemSlotAction;
        EquipItemSlot* m_pItemSlotConsumable;
        bool m_initialized = 0;

        void onCompleteLoadInventoryEquipGrid(cocos2d::Node* sender, cocos2d::Value data);

	};
}

#endif //LORAFEL_INVENTORYEQUIPGRID_H
