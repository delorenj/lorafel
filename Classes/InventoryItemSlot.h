//
// Created by Jarad DeLorenzo on 7/10/16.
//

#ifndef LORAFEL_INVENTORYITEMSLOT_H
#define LORAFEL_INVENTORYITEMSLOT_H

#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

namespace lorafel {
    class InventoryItemSlot : public cocos2d::Sprite {
    public:
        bool init() override;
        CREATE_FUNC(InventoryItemSlot);

        struct State {
            static const int EMPTY = 0;
            static const int IDLE = 1;
            static const int SELECTED = 2;
            static const int MOVING = 3;
        };

    protected:
        Item* m_pItem;
        int m_state = InventoryItemSlot::State::IDLE;
    };
}

#endif //LORAFEL_INVENTORYITEMSLOT_H
