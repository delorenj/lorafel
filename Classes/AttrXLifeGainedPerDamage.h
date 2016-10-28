//
// Created by Jarad M DeLorenzo on 10/22/16.
//

#ifndef LORAFEL_ATTRXLIFEGAINEDPERDAMAGE_H
#define LORAFEL_ATTRXLIFEGAINEDPERDAMAGE_H


#include "ItemAttribute.h"

namespace lorafel {
    class AttrXLifeGainedPerDamage : public ItemAttribute {
    public:
        AttrXLifeGainedPerDamage(cocos2d::Value& args) :
                ItemAttribute("{{value}}% Life Gained per Damage",
                        args.asValueMap()["value"].asString()) {
        }

        void invoke(cocos2d::Value& inout) {
            ItemAttribute::invoke(inout);
        }
    };
}

#endif //LORAFEL_ATTRXLIFEGAINEDPERDAMAGE_H
