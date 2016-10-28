//
// Created by Jarad M DeLorenzo on 10/28/16.
//

#ifndef LORAFEL_ATTRCHANCETOPOISONFORXTURNS_H
#define LORAFEL_ATTRCHANCETOPOISONFORXTURNS_H


#include "ItemAttribute.h"

namespace lorafel {
    class AttrChanceToPoisonForXTurns : public ItemAttribute {
    public:
        AttrChanceToPoisonForXTurns(cocos2d::Value& args) :
                ItemAttribute("Chance to Poison for {{value}} turns",
                        args.asValueMap()["value"].asString()) {
        }

        void invoke(cocos2d::Value& inout) {
            ItemAttribute::invoke(inout);
        }
    };
}

#endif //LORAFEL_ATTRCHANCETOPOISONFORXTURNS_H
