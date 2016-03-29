//
// Created by Jarad DeLorenzo on 3/28/16.
//

#ifndef LORAFEL_HEALTHPOTION_H
#define LORAFEL_HEALTHPOTION_H

#include "cocos2d.h"
#include "Consumable.h"


namespace lorafel {
    class HealthPotion : public Consumable {
    public:
        virtual bool init(double percent);

        static HealthPotion* create(double percent) {

            HealthPotion* pRet = new(std::nothrow) HealthPotion();
            if (pRet && pRet->init(percent)) {
                pRet->autorelease();
                return pRet;
            }
            else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

    protected:
        double m_amount;

    };
}

#endif //LORAFEL_HEALTHPOTION_H
