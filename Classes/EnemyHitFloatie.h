//
// Created by Jarad DeLorenzo on 1/27/16.
//

#ifndef LORAFEL_ENEMYHITFLOATIE_H
#define LORAFEL_ENEMYHITFLOATIE_H

#include "Floatie.h"

namespace lorafel {
    class EnemyHitFloatie : public Floatie {
    public:
        bool init(const int val);

        static EnemyHitFloatie* create(const int val) {
            EnemyHitFloatie *pRet = new(std::nothrow) EnemyHitFloatie();
            if (pRet && pRet->init(val)) {
                pRet->autorelease();
                return pRet;
            }
            else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

    };
}

#endif //LORAFEL_ENEMYHITFLOATIE_H
