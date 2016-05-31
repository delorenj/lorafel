//
// Created by Jarad DeLorenzo on 5/31/16.
//

#ifndef LORAFEL_HOOKACTION_H
#define LORAFEL_HOOKACTION_H

#include "PlayerMove.h"
#include "Arrow.h"

namespace lorafel {
    class HookAction : public PlayerMove {
    public:
        HookAction(SwappyGrid* pGrid, Arrow* pArrow) : PlayerMove(pGrid) {
            m_pArrow = pArrow;
        }

        virtual void run();
        virtual void cancel();
        virtual bool isValid();

    protected:
        Arrow* m_pArrow;
    };
}

#endif //LORAFEL_HOOKACTION_H
