//
// Created by Jarad M DeLorenzo on 10/22/16.
//

#include "AttrXLifeGainedPerDamage.h"

using namespace lorafel;

AttrXLifeGainedPerDamage::AttrXLifeGainedPerDamage(cocos2d::Value& args) :
        ItemAttribute("{{value}}% Life Gained per Damage",
                args.asValueMap()["value"].asString()) {
}

void AttrXLifeGainedPerDamage::invoke() {
    ItemAttribute::invoke();
}
