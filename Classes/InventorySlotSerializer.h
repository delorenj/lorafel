//
// Created by Jarad DeLorenzo on 8/2/16.
//

#ifndef LORAFEL_INVENTORYSLOTSERIALIZER_H
#define LORAFEL_INVENTORYSLOTSERIALIZER_H

#include "Serializer.h"
#include "StringPatch.h"
#include "Globals.h"

namespace lorafel {
    class InventorySlotSerializer : public Serializer<std::pair<int, int>, std::pair<std::string, int> > {
    public:
        virtual void serialize(std::pair<int, int> key, std::pair<std::string, int> value) override {
            auto hash = getHash(key);
            auto itemName = value.first;
            std::string stackSize;
            if(itemName == "") {
                stackSize = to_string(0);
            } else {
                stackSize = to_string(value.second);
            }
            auto combo = std::string(itemName + "|" + stackSize);
            cocos2d::UserDefault::getInstance()->setStringForKey(hash.c_str(), combo);
        }

        std::pair<std::string, int> unserialize(std::pair<int, int> key) override {
            auto hash = getHash(key);
            auto value = cocos2d::UserDefault::getInstance()->getStringForKey(hash.c_str());

            if(value == "") {
                return std::make_pair("", 0);
            }

            auto sep = value.find("|");
            auto itemName = value.substr(0, sep);
            auto stackSize = parseInt(value.substr(sep+1));

            return std::make_pair(itemName, stackSize);
        }

    protected:
        std::string getHash(std::pair<int, int> key) const {
            return  to_string(key.first) + "|" +  to_string(key.second);
        }
    };
}

#endif //LORAFEL_INVENTORYSLOTSERIALIZER_H
