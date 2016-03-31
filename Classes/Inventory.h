//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_INVENTORY_H
#define LORAFEL_INVENTORY_H

#include <unordered_map>
#include "Item.h"

namespace lorafel {
    class Inventory {
    public:
        typedef std::pair<Item*, int> ItemQuantityPair;
        typedef std::unordered_map<const char *, ItemQuantityPair> ItemDictionary;


    public:
        Inventory();
        virtual ~Inventory();

        const int addItem(const char* itemName, int quantity = 1);
        const int addItem(const char* itemName, Item* pItem, int quantity = 1);
        Item* getItem(const char* itemName);

    protected:
        ItemDictionary m_items;
        int getItemCount(const char* itemName);
        bool itemExists(const char* itemName);
    };

}
#endif //LORAFEL_INVENTORY_H
