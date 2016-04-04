//
// Created by Jarad DeLorenzo on 4/1/16.
//

#ifndef LORAFEL_HEALTHPOTIONPLAYERMOVE_H
#define LORAFEL_HEALTHPOTIONPLAYERMOVE_H

#include "PlayerMove.h"
#include "HealthPotion.h"
#include "Globals.h"

namespace lorafel {
    class HealthPotionPlayerMove : public PlayerMove {

    public:
        virtual void cancel();

        virtual bool isValid() override;
        virtual void run() override;

        HealthPotionPlayerMove(SwappyGrid* pGrid, int increaseHealthBy, Tile* pTarget) : PlayerMove(pGrid) {
            m_pTarget = pTarget;
            m_increaseHealthBy = increaseHealthBy;
            setTag(Tag::CONSUMABLE);
        }

    protected:
        Tile* m_pTarget;
        int m_increaseHealthBy;
    };
}

#endif //LORAFEL_HEALTHPOTIONPLAYERMOVE_H
