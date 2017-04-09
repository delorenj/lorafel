//
// Created by Jarad DeLorenzo on 7/9/16.
//

#ifndef LORAFEL_INVENTORYITEMGRID_H
#define LORAFEL_INVENTORYITEMGRID_H

#include "Globals.h"
#include "cocos2d.h"
#include "Grid.h"
#include "Item.h"
#include "ItemSlot.h"
#include "EquipItemSlot.h"

USING_NS_CC;

namespace lorafel {
    class Item;
    class InventoryItemSlot;
    class EquipItemSlot;
    class InventoryItemGrid : public cocos2d::Sprite {
    public:
        static const int NUM_ROWS = 4;
        static const int NUM_COLS = 8;
        typedef Grid<InventoryItemSlot*> ItemSlotPage;
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

        bool isEmpty(PaginatedCoords pair);
        PaginatedCoords nextEmptySlotCoordinates();

        Item* assignItemToSlot(std::pair<Item*, int>* pItemPair);
        Item* assignItemToSlot(Item* pItem, PaginatedCoords slotCoords);

        InventoryItemSlot* getSlotFromPosition(Vec2 coords);

        void highlightsOff();

        void swap(InventoryItemSlot* pSlot1, InventoryItemSlot* pSlot2);
        void swap(Coords pSlot1Coords, Coords pSlot2Coords);

        EquipItemSlot* getEquipSlotFromPosition(const Vec2& pos);

        InventoryItemSlot* getSlotFromCoords(PaginatedCoords pair) const;

        void loadInventory();

		bool isInitialized() const { return m_initialized; }

        void setInitialized(bool i);


    protected:
        std::shared_ptr<ItemSlotPage> m_pGrid;
        std::vector<std::shared_ptr<ItemSlotPage> >* m_pPages;
        std::shared_ptr<ItemSlotPage> createGrid();
        bool isStackable(Item* pItem);
        bool m_initialized = 0;
        int m_currentPage = 0;
        PaginatedCoords findNonMaxedSlotCoordinatesOfItem(Item* pItem);

        void onCompleteLoadInventoryItemGrid(cocos2d::Node* sender, cocos2d::Value data);
    };
}

#endif //LORAFEL_INVENTORYITEMGRID_H
