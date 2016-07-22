//
// Created by Jarad DeLorenzo on 7/9/16.
//

#ifndef LORAFEL_INVENTORYITEMGRID_H
#define LORAFEL_INVENTORYITEMGRID_H

#include "cocos2d.h"
#include "Grid.h"
#include "Item.h"
#include "ItemSlot.h"
#include "EquipItemSlot.h"

USING_NS_CC;

namespace lorafel {
    class InventoryItemSlot;
    class InventoryItemGrid : public cocos2d::Sprite {
    public:
        static const int NUM_ROWS = 4;
        static const int NUM_COLS = 8;
        typedef std::pair<int, int> Coords;

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

        bool isEmpty(Coords pair);
        Item* assignItemToSlot(std::pair<Item*, int>* pItemPair);
        Item* assignItemToSlot(Item* pItem, Coords slotCoords);

        InventoryItemSlot* getSlotFromPosition(Vec2 coords);

        void highlightsOff();

        void swap(InventoryItemSlot* pSlot1, InventoryItemSlot* pSlot2);
        void swap(std::pair<int, int> pSlot1Coords, std::pair<int, int> pSlot2Coords);

        EquipItemSlot* getEquipSlotFromPosition(const Vec2& pos);

    protected:
        void loadInventory();
        Coords nextEmptySlotCoordinates();


    protected:
        Grid<InventoryItemSlot*>* m_pGrid;


        bool isStackable(Item* pItem);

        Coords findNonMaxedSlotCoordinatesOfItem(Item* pItem);
    };
}

#endif //LORAFEL_INVENTORYITEMGRID_H
