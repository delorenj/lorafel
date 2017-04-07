//
// Created by Jarad DeLorenzo on 3/28/16.
//

#ifndef LORAFEL_ITEM_H
#define LORAFEL_ITEM_H

#include "cocos2d.h"
#include "SwappyGrid.h"
#include <string>
#include "StringPatch.h"
#include "ItemStat.h"
#include "IInventoryable.h"
#include "ItemNameGenerator.h"
#include "InventoryItemGrid.h"

USING_NS_CC;

namespace lorafel {
    class EquipItemSlot;
    class Item : public cocos2d::Sprite, public IInventoryable {
    public:
        virtual bool init() override;
        virtual void addEvents(cocos2d::Node* pNode);
        virtual bool addToInventory() override;
        virtual std::string getItemName();
        virtual void setItemName(const char* name) { m_itemName = to_string(name); }
        virtual void setItemName(std::string name) { m_itemName = name; }
        virtual std::string getClassName() const { return m_className; }
        virtual ValueMap getArguments() const { return m_arguments; }
        virtual void setArguments(ValueMap args) { m_arguments = args; }
        
        void addInventorySlotCoordinates(PaginatedCoords coords);
        std::set<PaginatedCoords> getInventorySlotCoordinates() const;


        void removeInventorySlotCoordinates(PaginatedCoords coords);

        void addEquipMask(int mask) { m_equipMaskSet.insert(mask); }
        bool canEquip(int mask) { return m_equipMaskSet.find(mask) != m_equipMaskSet.end(); }
		std::set<int> getEquipMasks() const { return m_equipMaskSet; }
		bool getUsesWholeEquipMaskSet() const { return m_usesWholeEquipMaskSet; }
        virtual void setEquipSlot(int equipMask);
        virtual bool isEquipped();
        virtual void unequip();

		std::string getId() const { return m_id; }
        void setId(std::string id) { m_id = id; }
        
        bool isStackable();
		std::set<ItemStat*>* getItemStats() const { return m_pItemStats; }
		std::set<ItemStat*>* getItemAttributes() const { return m_pItemAttributes; }
		void updateAttributes(cocos2d::ValueMap &args);
        SwappyGrid* getSwappyGrid() { return m_pSwappyGrid; }
		std::string getTileImage();

        void addEquipSlot(int i);

    protected:
        std::string m_id;
        std::string m_itemName;
        std::string m_className;
        ValueMap m_arguments;
        SwappyGrid* m_pSwappyGrid;
        std::set<PaginatedCoords> m_inventorySlotCoordinates;
        std::set<int> m_equipMaskSet;
		bool m_usesWholeEquipMaskSet = false;
		std::set<ItemStat*>* m_pItemStats;
		std::set<ItemStat*>* m_pItemAttributes;
        std::vector<int>* m_pEquipSlots;
    };
}

#endif //LORAFEL_ITEM_H
