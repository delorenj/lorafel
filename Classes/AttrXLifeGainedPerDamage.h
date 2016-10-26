//
// Created by Jarad M DeLorenzo on 10/22/16.
//

#ifndef LORAFEL_ATTRXLIFEGAINEDPERDAMAGE_H
#define LORAFEL_ATTRXLIFEGAINEDPERDAMAGE_H


#include "ItemAttribute.h"

namespace lorafel {
    class AttrXLifeGainedPerDamage : public ItemAttribute {
    public:
        AttrXLifeGainedPerDamage(cocos2d::Value& args);
        void invoke(cocos2d::Value& inout) override;
    };
}

#endif //LORAFEL_ATTRXLIFEGAINEDPERDAMAGE_H
