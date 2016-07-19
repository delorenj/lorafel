//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_INVENTORY_H
#define LORAFEL_INVENTORY_H

#include <unordered_map>
#include "Item.h"
#include "InventoryItemGrid.h"

namespace lorafel {
    class Inventory {
    public:
        typedef std::pair<Item*, int> ItemQuantityPair;
        typedef std::unordered_map<const char *, ItemQuantityPair*> ItemDictionary;
        typedef std::unordered_map<InventoryItemGrid::Coords, ItemQuantityPair*> SlotItemStackDictionary;
    public:
        Inventory() {
            m_pItemDictionary = new ItemDictionary();
            m_pSlotItemStackDictionary = new SlotItemStackDictionary();
        };
        virtual ~Inventory() {};
        void addEvents(cocos2d::Node* pSwappyGrid);

        const int addItem(Item* pItem, int quantity = 1);
        const int addItem(const char* itemName, int quantity = 1);
        const int addItem(const char* itemName, Item* pItem, int quantity = 1);
        Item* getItem(const char* itemName);
        ItemDictionary* getItemDictionary() { return m_pItemDictionary; }
        SlotItemStackDictionary* getSlotItemStackDictionary() { return m_pSlotItemStackDictionary; }

    protected:
        ItemDictionary* m_pItemDictionary;
        SlotItemStackDictionary* m_pSlotItemStackDictionary;
        int getItemCount(const char* itemName);
        bool itemExists(const char* itemName);
    };

}
#endif //LORAFEL_INVENTORY_H
