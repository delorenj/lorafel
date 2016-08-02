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
            cocos2d::UserDefault::getInstance()->setStringForKey(to_string(key).c_str(), value.c_str());
        }

        std::string unserialize(int key) override {
            return cocos2d::UserDefault::getInstance()->getStringForKey(to_string(key).c_str());
        }
    };
}

#endif //LORAFEL_EQUIPSTATUS_H
