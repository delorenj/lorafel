//
// Created by Jarad DeLorenzo on 3/28/16.
//

#ifndef LORAFEL_CONSUMABLE_H
#define LORAFEL_CONSUMABLE_H

#include "Item.h"
#include "Tile.h"
#include "IStackable.h"

namespace lorafel {
    class Consumable : public Item, public IStackable {
    public:
        virtual bool init() override;
        virtual void addEvents(cocos2d::Node* pNode) override;
        virtual void use(Tile* pTarget);

        virtual void equip(EquipItemSlot* pSlot) override;

        virtual int getMaxStack() const override { return m_maxStack; }

    protected:
        int m_maxStack = 20;
    };
}

#endif //LORAFEL_CONSUMABLE_H
