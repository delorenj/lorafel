//
// Created by Jarad DeLorenzo on 4/14/17.
//

#include "TimedContinuousStatEffect.h"
#include "StatEffect.h"
#include "EventDataInteger.h"

using namespace lorafel;

bool StatEffect::init() {
    return cocos2d::Node::init();
}

void StatEffect::setTotalStatDelta(int delta) {
    m_delta = delta;
}

void StatEffect::setStatEvent(std::string eventName) {
    m_eventName = eventName;
}

void StatEffect::start() {
    schedule(schedule_selector(StatEffect::fireTrigger), 1.0f);
}

void StatEffect::fireTrigger(float delta) {
    auto data = new EventDataInteger(-10);
    getEventDispatcher()->dispatchCustomEvent(m_eventName, data);
}
