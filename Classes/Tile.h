//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILE_H
#define LORAFEL_TILE_H

#include "cocos2d.h"

namespace lorafel {
    class Tile : public cocos2d::Sprite {

    public:
        bool init() override;

        void update(float delta) override;

        CREATE_FUNC(Tile);

        std::string getSpriteName();
        void setSpriteName(std::string name);
        void initOptions();

    protected:
        std::string spriteName;

    };
}

#endif //LORAFEL_TILE_H
