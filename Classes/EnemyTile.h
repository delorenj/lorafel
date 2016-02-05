//
// Created by Jarad DeLorenzo on 1/25/16.
//

#ifndef LORAFEL_ENEMYTILE_H
#define LORAFEL_ENEMYTILE_H

#include "Tile.h"
#include "CharacterTile.h"

namespace lorafel {
    class EnemyTile : public CharacterTile {
    public:
        virtual bool init() override;
        virtual bool isEnemy() override {
                return true;
        }
    };
}

#endif //LORAFEL_ENEMYTILE_H
