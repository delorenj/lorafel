//
// Created by Jarad DeLorenzo on 2/3/16.
//

#ifndef LORAFEL_BASICTURNMANAGER_H
#define LORAFEL_BASICTURNMANAGER_H


#include "TurnManager.h"

USING_NS_CC;

namespace lorafel {
    class BasicTurnManager : public TurnManager {
    public:
        BasicTurnManager();
        virtual Tile *getNextPlayerTile() override;
    };
}
#endif //LORAFEL_BASICTURNMANAGER_H
