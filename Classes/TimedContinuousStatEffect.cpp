//
// Created by Jarad DeLorenzo on 4/14/17.
//

#include "TimedContinuousStatEffect.h"

using namespace lorafel;

bool TimedContinuousStatEffect::init() {
    return StatEffect::init();
}

void TimedContinuousStatEffect::setDurationInSeconds(int seconds) {
    m_durationInSeconds = seconds;
}

