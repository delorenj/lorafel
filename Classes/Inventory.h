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
        typedef std::unordered_map<char *, ItemQuantityPair> ItemDictionary;
    public:
        Inventory();
        virtual ~Inventory();

        const int addItem(char* itemName, int quantity = 1);
        const int addItem(char* itemName, Item* pItem, int quantity = 1);
    protected:
        ItemDictionary m_items;

        int getItemCount(char* itemName);

        bool itemExists(char* itemName);
    };

}
#endif //LORAFEL_INVENTORY_H
