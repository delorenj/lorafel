//
// Created by Jarad DeLorenzo on 3/15/16.
//

#ifndef LORAFEL_FIREBALLACTION_H
#define LORAFEL_FIREBALLACTION_H

#include "PlayerMove.h"

namespace lorafel {
    class FireballAction : public PlayerMove {
    public:
        FireballAction(SwappyGrid* pGrid, Tile* pTile)
                : PlayerMove(pGrid) {
            m_pTile = pTile;
        }

        virtual void run();
        virtual void cancel();
        virtual bool isValid();

    protected:
        Tile* m_pTile;
    };
}

#endif //LORAFEL_FIREBALLACTION_H
