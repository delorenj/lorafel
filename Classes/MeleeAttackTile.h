//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_MELEEATTACKTILE_H
#define LORAFEL_MELEEATTACKTILE_H

#include "Tile.h"

namespace lorafel {
    class MeleeAttackTile : public Tile {
    public:
        void onMatch(Match* pMatch) override;

        static MeleeAttackTile *create(cocos2d::ValueMap args) {
            MeleeAttackTile * pRet = new(std::nothrow) MeleeAttackTile();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }
    };
}
#endif //LORAFEL_MELEEATTACKTILE_H
