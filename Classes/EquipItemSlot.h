//
// Created by Jarad DeLorenzo on 7/21/16.
//

#ifndef LORAFEL_EQUIPITEMSLOT_H
#define LORAFEL_EQUIPITEMSLOT_H

#include "ItemSlot.h"

USING_NS_CC;

namespace lorafel {
    class EquipItemSlot : public ItemSlot {
    public:
        bool init() override;

        CREATE_FUNC(EquipItemSlot);

        virtual void onItemSelected(cocos2d::EventCustom* event);
        virtual void onItemUnselected();
        virtual void setItem(Item* pItem, int stackSize) override;
        void setEquipMask(int mask) { m_equipMask = mask; }
        int getEquipMask() const { return m_equipMask; }

        virtual void addEvents() override;

    protected:
        int m_equipMask;


    };
}

#endif //LORAFEL_EQUIPITEMSLOT_H
