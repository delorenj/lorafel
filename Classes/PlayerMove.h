//
// Created by Jarad DeLorenzo on 1/4/16.
//

#ifndef LORAFEL_PLAYERMOVE_H
#define LORAFEL_PLAYERMOVE_H

#include "SwappyGrid.h"

namespace lorafel {
    class SwappyGrid;
    class PlayerMove {
    public:
        PlayerMove(SwappyGrid* pGrid) : m_pSwappyGrid(pGrid) { };

        virtual ~PlayerMove() {
            CC_SAFE_DELETE(m_pActions);
        };

        virtual void run() = 0;
        virtual void cancel() = 0;
        virtual bool isValid() = 0;

        const std::vector<cocos2d::Action*>* getActions() const { return m_pActions; }

    protected:
        SwappyGrid* m_pSwappyGrid;
        std::vector<cocos2d::Action*>* m_pActions;
    };
}

#endif //LORAFEL_PLAYERMOVE_H
