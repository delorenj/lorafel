//
// Created by Jarad DeLorenzo on 4/8/16.
//

#ifndef LORAFEL_MATCH5_H
#define LORAFEL_MATCH5_H

#include "Match.h"

namespace lorafel {
    class Match5 : public Match {

    public:
        static Match* create(std::set<Tile*>& tileSet)
        {
            Match *pRet = new(std::nothrow) Match5();
            if (pRet && pRet->init(tileSet))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        virtual void run() override;
    };
}

#endif //LORAFEL_MATCH5_H
