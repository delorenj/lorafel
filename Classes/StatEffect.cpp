//
// Created by Jarad DeLorenzo on 4/14/17.
//

#include "TimedContinuousStatEffect.h"
#include "StatEffect.h"

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