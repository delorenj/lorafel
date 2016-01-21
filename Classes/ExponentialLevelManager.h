//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_EXPONENTIALLEVELMANAGER_H
#define LORAFEL_EXPONENTIALLEVELMANAGER_H

#include "LevelManager.h"

namespace lorafel {

    class ExponentialLevelManager : public LevelManager {
    public:
        ExponentialLevelManager() : LevelManager(0) {} ;
        ExponentialLevelManager(unsigned long xp) : LevelManager(xp) {} ;


    };

}

#endif //LORAFEL_EXPONENTIALLEVELMANAGER_H
