//
// Created by Jarad DeLorenzo on 4/14/17.
//

#include "TimedContinuousStatEffect.h"
#include "EventDataInteger.h"
#include "Globals.h"

using namespace lorafel;

bool TimedContinuousStatEffect::init() {
    if(!StatEffect::init()) {
        return false;
    }

    return true;
}

void TimedContinuousStatEffect::setDurationInSeconds(int seconds) {
    m_durationInSeconds = seconds;
}

void TimedContinuousStatEffect::start() {
    m_valFragment = ROUND_2_INT((float)((float)m_delta / (float)m_durationInSeconds));
    m_remainingLoops = m_durationInSeconds;
    CCLOG("m_delta=%d, m_durationInSeconds=%d, m_valFragment=%f", m_delta, m_durationInSeconds, m_valFragment);
    schedule(schedule_selector(StatEffect::fireTrigger), UPDATE_INTERVAL_IN_SECONDS);
}

void TimedContinuousStatEffect::fireTrigger(float delta) {
    if(m_remainingLoops > 0) {
        auto data = new EventDataInteger(m_valFragment);
        getEventDispatcher()->dispatchCustomEvent(m_eventName, data);
        m_remainingLoops--;
    } else {
        unscheduleAllCallbacks();
    }
}

