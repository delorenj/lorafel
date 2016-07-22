//
// Created by Jarad DeLorenzo on 3/28/16.
//

#ifndef LORAFEL_ITEM_H
#define LORAFEL_ITEM_H

#include "cocos2d.h"
#include "SwappyGrid.h"
#include <string>
#include "StringPatch.h"

USING_NS_CC;

namespace lorafel {
    class Item : public cocos2d::Sprite {
    public:
        virtual bool init() override;
        virtual void addEvents(cocos2d::Node* pNode);
        virtual bool addToInventory() = 0;
        virtual const char* getItemName() const { return m_itemName; }
        virtual void setItemName(const char* name) { m_itemName = name; }

        void addInventorySlotCoordinates(std::pair<int, int> coords);
        std::set<std::pair<int, int> > getInventorySlotCoordinates() const;


        void removeInventorySlotCoordinates(std::pair<int, int> coords);

        void addEquipMask(int mask) { m_equipMaskSet.insert(mask); }
        bool canEquip(int mask) { return m_equipMaskSet.find(mask) != m_equipMaskSet.end(); }

    protected:
        const char* m_itemName;
        SwappyGrid* m_pSwappyGrid;
        std::set<std::pair<int, int> > m_inventorySlotCoordinates;
        std::set<int> m_equipMaskSet;
    };
}

#endif //LORAFEL_ITEM_H
