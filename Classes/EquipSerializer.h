//
// Created by Jarad DeLorenzo on 7/29/16.
//

#ifndef LORAFEL_EQUIPSTATUS_H
#define LORAFEL_EQUIPSTATUS_H

#include "Serializer.h"
#include "StringPatch.h"

namespace lorafel {
    class EquipSerializer : public Serializer<int, std::string> {
    public:
        void serialize(int key, std::string value) override {
//            cocos2d::UserDefault::getInstance()->setStringForKey(to_string(key).c_str(), value.c_str());
            auto hash = getHash(key);
            auto itemName = value.first;
            std::string stackSize;
            if(itemName == "") {
                stackSize = to_string(0);
            } else {
                stackSize = to_string(value.second);
            }
            /**
             * If clearing out a slot,
             * delete instead of insert
             */
            if(itemName == "" || stackSize == "0") {
                FirebaseDatabase::getInstance()->deleteKey(hash.c_str(), "inventory_item_grid");
            } else {
                auto combo = std::string(itemName + "|" + stackSize);
                FirebaseDatabase::getInstance()->setStringForKey(hash.c_str(), combo, "inventory_item_grid");
            }
        }

        std::string unserialize(int key) {
            return cocos2d::UserDefault::getInstance()->getStringForKey(to_string(key).c_str());
        }
    };
}

#endif //LORAFEL_EQUIPSTATUS_H
