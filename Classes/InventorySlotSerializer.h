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
    class InventorySlotSerializer : public Serializer<PaginatedCoords,
                                            std::pair<std::string, int> > {
    public:
        virtual void serialize(PaginatedCoords key, std::pair<std::string, int> value) override {
            auto hash = getHash(key);
            auto itemId = value.first;
            std::string stackSize;
            if(itemId == "") {
                stackSize = to_string(0);
            } else {
                stackSize = to_string(value.second);
            }
            /**
             * If clearing out a slot,
             * delete instead of insert
             */
            if(itemId == "" || stackSize == "0") {
                FirebaseDatabase::getInstance()->deleteKey(hash.c_str(), "inventory_item_grid");
                FirebaseDatabase::getInstance()->deleteKey("", "inventory_item_grid_min_stack");
            } else {
                auto combo = std::string(itemId + "|" + stackSize);
                FirebaseDatabase::getInstance()->setStringForKey(hash.c_str(), combo, "inventory_item_grid");

                ValueMap vm;
                vm["key"] = hash;
                vm["value"] = stackSize;

                FirebaseDatabase::getInstance()->addMapToKey(itemId, vm, "inventory_item_grid_min_stack");
            }
        }

        std::map<PaginatedCoords, std::pair<std::string, int> > unserialize(Value data) {
            std::map<PaginatedCoords, std::pair<std::string, int> > result;
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
                        auto itemId = value.substr(0, sep);
                        auto stackSize = parseInt(value.substr(sep+1));

                        pair = std::make_pair(itemId, stackSize);
                    }
                    result[idx] = pair;
                }
            }
            return result;
        }

    protected:
        std::string getHash(PaginatedCoords key) const {
            return  to_string(key.page) + ":" + to_string(key.coords.first) + "|" +  to_string(key.coords.second);
        }

        PaginatedCoords hashToIdx(std::string key) const {
            auto sep = key.find(":");
            auto page = parseInt(key.substr(0, sep));
            auto coords = key.substr(sep+1);
            sep = coords.find("|");
            auto i = parseInt(coords.substr(0, sep));
            auto j = parseInt(coords.substr(sep+1));
            PaginatedCoords pc;
            pc.page = page;
            pc.coords = std::make_pair(i,j);
            return pc;
        }

    };
}

#endif //LORAFEL_INVENTORYSLOTSERIALIZER_H
