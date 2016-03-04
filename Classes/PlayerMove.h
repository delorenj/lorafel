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
            CCLOG("~PlayerMove()");
            if(m_pActions != nullptr) {
                if(m_pActions->size() > 0) {
                    for( auto it : *m_pActions) {
                        CC_SAFE_DELETE(it);
                    }
                }
            }
        };

        virtual void run() = 0;
        virtual void cancel() = 0;
        virtual bool isValid() = 0;

        bool isMatched() { return m_isMatched; }
        bool setMatched(bool matched) { m_isMatched = matched; }
        const std::vector<cocos2d::Action*>* getActions() const { return m_pActions; }

    protected:
        SwappyGrid* m_pSwappyGrid;
        std::vector<cocos2d::Action*>* m_pActions;
        bool m_isMatched = 0;
    };
}

#endif //LORAFEL_PLAYERMOVE_H
