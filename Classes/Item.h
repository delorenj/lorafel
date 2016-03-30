//
// Created by Jarad DeLorenzo on 3/28/16.
//

#ifndef LORAFEL_ITEM_H
#define LORAFEL_ITEM_H

#include "cocos2d.h"

namespace lorafel {
    class Item : public cocos2d::Sprite {
    public:
        virtual bool init() override;
    };
}

#endif //LORAFEL_ITEM_H
