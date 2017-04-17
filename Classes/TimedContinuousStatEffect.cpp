//
// Created by Jarad DeLorenzo on 4/14/17.
//

#include "TimedContinuousStatEffect.h"
#include "EventDataInteger.h"
#include "Globals.h"
#include "PlayerManager.h"

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

bool TimedContinuousStatEffect::start() {
    auto player = PlayerManager::getInstance()->getPlayer();
    if(player->hasBuffDebuff(getBuffDebuffTag())) {
        return false;
    }

    player->addBuffDebuff(getBuffDebuffTag());

    m_valFragment = ROUND_2_INT((float)((float)m_delta / (float)m_durationInSeconds));
    m_remainingLoops = m_durationInSeconds;
    CCLOG("m_delta=%d, m_durationInSeconds=%d, m_valFragment=%d", m_delta, m_durationInSeconds, m_valFragment);
    getScheduler()->schedule([&](float dt) {
        CCLOG("FIRING!: m_delta=%d, m_durationInSeconds=%d, m_valFragment=%d", m_delta, m_durationInSeconds, m_valFragment);
        fireTrigger(dt);
    }, this, UPDATE_INTERVAL_IN_SECONDS, false, "schedulerKey");

    return true;
}

void TimedContinuousStatEffect::fireTrigger(float delta) {
    if(m_remainingLoops > 0) {
        auto data = new EventDataInteger(m_valFragment);
        getEventDispatcher()->dispatchCustomEvent(m_eventName, data);
        m_remainingLoops--;
    } else {
        unscheduleAllCallbacks();
        PlayerManager::getInstance()->getPlayer()->removeBuffDebuff(m_buffDebuffTag);
    }
}

