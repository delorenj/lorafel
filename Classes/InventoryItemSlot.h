//
// Created by Jarad DeLorenzo on 7/10/16.
//

#ifndef LORAFEL_INVENTORYITEMSLOT_H
#define LORAFEL_INVENTORYITEMSLOT_H

#include "cocos2d.h"
#include "Item.h"
#include "Globals.h"
#include "InventoryItemGrid.h"

USING_NS_CC;

namespace lorafel {
    class InventoryItemSlot : public cocos2d::Sprite {
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

        struct State {
            static const int EMPTY = 0;
            static const int IDLE = 1;
            static const int SELECTED = 2;
            static const int TOUCH_BEGIN = 3;
            static const int MOVE_BEGIN = 4;
            static const int MOVING = 5;
            static const int MOVE_END = 6;
            static const int TOUCH_END = 7;
        };

        void setItem(Item* pItem, int stackSize = 1);

        Item* getItem() const { return m_pItem; }

        bool isEmpty();
        int incrementStack();
        int decrementStack();
        bool stackFull() const;
        int getStackSize() const { return m_stackSize; }
        void setStackSize(int stackSize);
        void ghostOn() const;
        void ghostOff() const;
        cocos2d::Sprite* getGhost() const { return m_pGhost; }
        void highlightOn();
        void highlightOff();
        void update(float delta) override;
        std::pair<int, int> getCoords() const { return m_coords; }
        void setCoords(std::pair<int, int> coords) { m_coords = coords; }

    protected:
        Item* m_pItem;
        InventoryItemGrid* m_pGrid;
        cocos2d::Sprite* m_pItemSprite;
        cocos2d::Sprite* m_pGhost;
        cocos2d::Label* m_pStackSizeLabel;
        std::pair<int, int> m_coords;
        int m_state = InventoryItemSlot::State::EMPTY;
        int m_stackSize = 0;
        bool m_stackSizeChange = false;
        void addEvents();

    };
}

#endif //LORAFEL_INVENTORYITEMSLOT_H
