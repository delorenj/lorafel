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
    class EquipItemSlot;
    class Item : public cocos2d::Sprite {
    public:
        virtual bool init() override;
        virtual void addEvents(cocos2d::Node* pNode);
        virtual bool addToInventory() = 0;
        virtual std::string getItemName() const { return m_itemName; }
        virtual void setItemName(const char* name) { m_itemName = to_string(name); }
        virtual void setItemName(std::string name) { m_itemName = name; }
        virtual std::string getClassName() const { return m_className; }
        virtual ValueVector getArguments() const { return m_arguments; }
        virtual void setArguments(ValueVector args) { m_arguments = args; }
        
        void addInventorySlotCoordinates(std::pair<int, int> coords);
        std::set<std::pair<int, int> > getInventorySlotCoordinates() const;


        void removeInventorySlotCoordinates(std::pair<int, int> coords);

        void addEquipMask(int mask) { m_equipMaskSet.insert(mask); }
        bool canEquip(int mask) { return m_equipMaskSet.find(mask) != m_equipMaskSet.end(); }

        virtual void addEquipSlot(EquipItemSlot* pSlot);
        virtual bool isEquipped();

        void removeEquipSlot(EquipItemSlot* pSlot);
        std::string getId() const { return m_id; }
        void setId(std::string id) { m_id = id; }

        bool isStackable();

    protected:
        std::string m_id;
        std::string m_itemName;
        std::string m_className;
        ValueVector m_arguments;
        SwappyGrid* m_pSwappyGrid;
        std::set<std::pair<int, int> > m_inventorySlotCoordinates;
        std::set<int> m_equipMaskSet;
        std::set<EquipItemSlot*> m_pEquipSlots;
    };
}

#endif //LORAFEL_ITEM_H
