//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_EXPONENTIALLEVELMANAGER_H
#define LORAFEL_EXPONENTIALLEVELMANAGER_H

#include "XpManager.h"

namespace lorafel {

    class ExponentialXpManager : public XpManager {
    public:
        ExponentialXpManager() : XpManager(0) {} ;
        ExponentialXpManager(unsigned long xp) : XpManager(xp) {} ;


    };

}

#endif //LORAFEL_EXPONENTIALLEVELMANAGER_H
