//
// Created by Jarad DeLorenzo on 4/22/16.
//

#ifndef LORAFEL_HOOKACTIONTILE_H
#define LORAFEL_HOOKACTIONTILE_H

#include "ToggleActionTile.h"

namespace lorafel {
    class HookActionTile : public ToggleActionTile {
    public:
        bool init() override;
        CREATE_FUNC(HookActionTile);

    protected:
        void toggleAction() override;
    };
}

#endif //LORAFEL_HOOKACTIONTILE_H
