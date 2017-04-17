//
// Created by Jarad DeLorenzo on 4/14/17.
//

#include "Globals.h"
#include "TimedContinuousStatEffect.h"
#include "StatEffect.h"
#include "EventDataInteger.h"

using namespace lorafel;

bool StatEffect::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }

    setTag(Tag::STAT_EFFECT);
    return true;
}

void StatEffect::setTotalStatDelta(int delta) {
    m_delta = delta;
}

void StatEffect::setStatEvent(std::string eventName) {
    m_eventName = eventName;
}

bool StatEffect::start() {
    scheduleOnce(schedule_selector(StatEffect::fireTrigger), 1.0f);
}

void StatEffect::fireTrigger(float delta) {
    auto data = new EventDataInteger(m_delta);
    getEventDispatcher()->dispatchCustomEvent(m_eventName, data);
}
