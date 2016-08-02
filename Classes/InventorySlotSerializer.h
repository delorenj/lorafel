//
// Created by Jarad DeLorenzo on 8/2/16.
//

#ifndef LORAFEL_INVENTORYSLOTSERIALIZER_H
#define LORAFEL_INVENTORYSLOTSERIALIZER_H

#include "Serializer.h"
#include "Item.h"
#include "StringPatch.h"

namespace lorafel {
    typedef std::pair<int, int> Key;
    typedef std::pair<Item*, int> Value;

    class InventorySlotSerializer : public Serializer<std::pair<int, int>, std::pair<Item*, int> > {
    public:
        virtual void serialize(Key key, Value value) override {
            std::hash<Key> hash;
            hash.operator()(key);
            cocos2d::Data data;
            auto pItem = value.first;
            auto name = pItem->getItemName();
            auto stackSize = to_string(value.second);
            auto combo = std::string(name + "|" + stackSize);
            cocos2d::UserDefault::getInstance()->setStringForKey(to_string(hash).c_str(), combo);
        }
    };
}

#endif //LORAFEL_INVENTORYSLOTSERIALIZER_H
