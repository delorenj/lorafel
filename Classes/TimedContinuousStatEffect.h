//
// Created by Jarad DeLorenzo on 4/14/17.
//

#ifndef LORAFEL_TIMEDCONTINUOUSSTATEFFECT_H
#define LORAFEL_TIMEDCONTINUOUSSTATEFFECT_H

#include "StatEffect.h"

namespace lorafel {
    class TimedContinuousStatEffect : public StatEffect {
    public:
        CREATE_FUNC(TimedContinuousStatEffect);
        virtual bool init() override;
        const float UPDATE_INTERVAL_IN_SECONDS = 1.0f;
        void setDurationInSeconds(int seconds);
        virtual void start() override;
        virtual void fireTrigger(float delta) override;
    protected:
        int m_durationInSeconds;
        int m_valFragment = 0;
        int m_remainingLoops = 0;
    };
}

#endif //LORAFEL_TIMEDCONTINUOUSSTATEFFECT_H
