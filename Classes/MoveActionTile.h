//
// Created by Jarad DeLorenzo on 4/22/16.
//

#ifndef LORAFEL_MOVEACTIONTILE_H
#define LORAFEL_MOVEACTIONTILE_H

#include "ToggleActionTile.h"


namespace lorafel {

    class MoveActionTile : public ToggleActionTile {
    public:
        bool init() override;
        CREATE_FUNC(MoveActionTile);

    protected:
        void toggleAction();
    };
};


#endif //LORAFEL_MOVEACTIONTILE_H
