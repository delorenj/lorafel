//
// Created by Jarad DeLorenzo on 6/10/16.
//

#ifndef LORAFEL_CHARACTERBUTTON_H
#define LORAFEL_CHARACTERBUTTON_H

#include "cocos2d.h"

namespace lorafel {
    class InGameModalNavButton : public cocos2d::Sprite {
    public:
        virtual bool init() override ;
        void addEvents();

        CREATE_FUNC(InGameModalNavButton);
    };
}

#endif //LORAFEL_CHARACTERBUTTON_H
