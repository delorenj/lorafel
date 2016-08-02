//
// Created by Jarad DeLorenzo on 7/29/16.
//

#ifndef LORAFEL_EQUIPSTATUS_H
#define LORAFEL_EQUIPSTATUS_H

#include "Serializer.h"

namespace lorafel {
    class EquipSerializer : public cocos2d::Node, Serializer<int, std::string> {
    public:
        CREATE_FUNC(EquipSerializer);

        std::string getItemNameByEquipMask(int mask) const;
        virtual void serialize(int key, std::string value) override;

    };
}

#endif //LORAFEL_EQUIPSTATUS_H
