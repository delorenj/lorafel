//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_INVENTORY_H
#define LORAFEL_INVENTORY_H

#include <unordered_map>
#include "Item.h"

namespace std {
    template<>
    struct hash<std::pair<int, int> > {
        size_t operator()(const std::pair<int, int>& pt) const {
            return std::hash<int>()(pt.first) ^ std::hash<int>()(pt.second);
        }
    };
}

namespace lorafel {
    class Inventory {
    public:
        typedef std::pair<Item*, int> ItemQuantityPair;
        typedef std::unordered_map<std::string, ItemQuantityPair*> ItemDictionary;
        typedef std::unordered_map<std::pair<int, int>, ItemQuantityPair*> SlotItemStackDictionary;

		int removeItem(std::string itemId, int quantity);

	public:
        Inventory() {
            m_pItemDictionary = new ItemDictionary();
            m_pSlotItemStackDictionary = new SlotItemStackDictionary();
        };
        virtual ~Inventory() {};
        void addEvents(cocos2d::Node* pSwappyGrid);

        const int addItem(Item* pItem, int quantity = 1);
        Item* getItem(std::string itemId);
        ItemDictionary* getItemDictionary() { return m_pItemDictionary; }
        SlotItemStackDictionary* getSlotItemStackDictionary() { return m_pSlotItemStackDictionary; }
        int getItemCount(std::string itemName);

    protected:
        ItemDictionary* m_pItemDictionary;
        SlotItemStackDictionary* m_pSlotItemStackDictionary;
        bool itemExists(std::string itemName);
	};

}
#endif //LORAFEL_INVENTORY_H
