//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "HealthPotion.h"

using namespace lorafel;

bool HealthPotion::init(double amount) {
    if(!Consumable::init()) {
        return false;
    }

    m_amount = amount;
    initWithSpriteFrameName("PoisonGlyph.png");
    return true;
}
