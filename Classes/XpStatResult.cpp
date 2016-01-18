//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "XpStatResult.h"

using namespace lorafel;

void XpStatResult::apply() {
    CCLOG("+%d XP", m_multiplier*m_val);
}
