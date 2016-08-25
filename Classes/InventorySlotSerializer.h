//
// Created by Jarad DeLorenzo on 8/2/16.
//

#ifndef LORAFEL_INVENTORYSLOTSERIALIZER_H
#define LORAFEL_INVENTORYSLOTSERIALIZER_H

#include "Serializer.h"
#include "StringPatch.h"
#include "Globals.h"
#include "FirebaseDatabase.h"

namespace lorafel {
    class InventorySlotSerializer : public Serializer<std::pair<int, int>,
                                            std::pair<std::string, int> > {
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
//            cocos2d::UserDefault::getInstance()->setStringForKey(hash.c_str(), combo);
            FirebaseDatabase::getInstance()->setStringForKey(hash.c_str(), combo, "inventory_item_grid");
        }

        std::map<std::pair<int, int>, std::pair<std::string, int> > unserialize(Value data) {
            std::map<std::pair<int, int>, std::pair<std::string, int> > result;
            if (!data.isNull() && data.getType() == Value::Type::MAP) {
                ValueMap slotLayouts = data.asValueMap();
                for(auto slotLayout : slotLayouts) {
                    std::string key = slotLayout.first;
                    std::string value = slotLayout.second.asString();
                    std::pair<std::string, int> pair;

                    auto idx = hashToIdx(key);

                    if(value == "") {
                        pair = std::make_pair("", 0);
                    } else {
                        auto sep = value.find("|");
                        auto itemName = value.substr(0, sep);
                        auto stackSize = parseInt(value.substr(sep+1));

                        pair = std::make_pair(itemName, stackSize);
                    }
                    result[idx] = pair;
                }
            }
            return result;
        }

    protected:
        std::string getHash(std::pair<int, int> key) const {
            return  to_string(key.first) + "|" +  to_string(key.second);
        }

        std::pair<int,int> hashToIdx(std::string key) const {
            auto sep = key.find("|");
            auto i = parseInt(key.substr(0, sep));
            auto j = parseInt(key.substr(sep+1));

            return std::make_pair(i,j);
        }

    };
}

#endif //LORAFEL_INVENTORYSLOTSERIALIZER_H
