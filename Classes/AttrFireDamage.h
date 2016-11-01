//
// Created by Jarad M DeLorenzo on 10/29/16.
//

#ifndef LORAFEL_ATTRFIREDAMAGE_H
#define LORAFEL_ATTRFIREDAMAGE_H


#include "ItemAttribute.h"

namespace lorafel {
    class AttrFireDamage : public ItemAttribute {
    public:
        AttrFireDamage(cocos2d::Value& args) :
                ItemAttribute("+{{value}} Fire Damage",
                        args.asValueMap()["value"].asString()) {
        }

        void invoke(cocos2d::Value& inout) {
            ItemAttribute::invoke(inout);
        }
    };
}

#endif //LORAFEL_ATTRFIREDAMAGE_H
