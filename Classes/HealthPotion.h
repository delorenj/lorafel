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
        virtual bool init(ValueMap args);

        static HealthPotion* create(cocos2d::ValueMap args) {

            HealthPotion* pRet = new(std::nothrow) HealthPotion();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            }
            else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        virtual void addEvents(cocos2d::Node* pNode) override;
        virtual void use(Tile* pTarget) override;
        virtual int getMaxStack() const override { return 5; }

    protected:
        void initItemName();
        float m_amount;

    };
}

#endif //LORAFEL_HEALTHPOTION_H
