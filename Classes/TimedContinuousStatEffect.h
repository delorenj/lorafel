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
        void setDurationInSeconds(int seconds);

    protected:
        int m_durationInSeconds;
    };
}

#endif //LORAFEL_TIMEDCONTINUOUSSTATEFFECT_H
