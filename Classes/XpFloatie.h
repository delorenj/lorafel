//
// Created by Jarad DeLorenzo on 1/22/16.
//

#ifndef LORAFEL_XPFLOATIE_H
#define LORAFEL_XPFLOATIE_H

#include "Floatie.h"

namespace lorafel {
    class XpFloatie : public Floatie {
    public:
        bool init(const int val);
        void update(float dt) override;

        static XpFloatie* create(const int val) {
            XpFloatie *pRet = new(std::nothrow) XpFloatie();
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

#endif //LORAFEL_XPFLOATIE_H
