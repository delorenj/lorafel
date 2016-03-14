//
// Created by Jarad DeLorenzo on 3/14/16.
//

#ifndef LORAFEL_FIREBALLACTIONTILE_H
#define LORAFEL_FIREBALLACTIONTILE_H

#include "ActionTile.h"

namespace lorafel {
    class FireballActionTile : public ActionTile {
    public:
        bool init() override;
        CREATE_FUNC(FireballActionTile);
    };
}

#endif //LORAFEL_FIREBALLACTIONTILE_H
