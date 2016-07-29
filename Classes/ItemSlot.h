//
// Created by Jarad DeLorenzo on 7/21/16.
//

#ifndef LORAFEL_ITEMSLOT_H
#define LORAFEL_ITEMSLOT_H

#include "Item.h"
#include "InventoryItemGrid.h"

namespace lorafel {
    class ItemSlot : public cocos2d::Sprite {
    public:
        virtual bool init() override;

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

        Item* getItem() const { return m_pItem; }

        Sprite* getGhost() const { return m_pGhost; }

        bool isEmpty();
        void ghostOn() const;
        void ghostOff() const;
        void highlightOn();
        void highlightOff();
        int incrementStack();
        int decrementStack();
        bool stackFull() const;
        int getStackSize() const { return m_stackSize; }
        void setStackSize(int stackSize);
        double getOriginalScale() const { return m_originalScale; }
        void setOriginalScale(double scale) { m_originalScale = scale; }

        /**
         * Each type of ItemSlot is different, so this is
         * a pure virtual function and needs to be implemented
         * for each ItemSlot subclass
         */
        virtual void setItem(Item* pItem, int stackSize = 1) = 0;

        void update(float delta) override;

    protected:
        virtual void addEvents();

    protected:
        Item* m_pItem;
        cocos2d::Sprite* m_pItemSprite;
        cocos2d::Sprite* m_pGhost;
        cocos2d::Label* m_pStackSizeLabel;
        int m_stackSize = 0;
        bool m_stackSizeChange = false;
        double m_originalScale;
        int m_state = ItemSlot::State::EMPTY;
    };

}


#endif //LORAFEL_ITEMSLOT_H
