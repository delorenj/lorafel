//
// Created by Jarad DeLorenzo on 4/17/17.
//

#ifndef LORAFEL_DEBUFFPOISON_H
#define LORAFEL_DEBUFFPOISON_H

#import "TimedContinuousStatEffect.h"
#import "PlayerManager.h"

namespace lorafel {
    class DebuffPoison : public TimedContinuousStatEffect {
    public:
        CREATE_FUNC(DebuffPoison);
        virtual bool init() override {
            return TimedContinuousStatEffect::init();
        }

        virtual bool start() override {
            setStatTag(BuffDebuffTag::POISONED);
            setDurationInSeconds(5);
            setTotalStatDelta(ROUND_2_INT(PlayerManager::getInstance()->getPlayer()->getMaxHp() * -0.25f));
            setStatEvent("update_hp");
            return TimedContinuousStatEffect::start();
        }
    };
}

#endif //LORAFEL_DEBUFFPOISON_H
