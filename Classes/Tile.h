//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILE_H
#define LORAFEL_TILE_H

#include "cocos2d.h"
#include "SwappyGrid.h"

namespace lorafel {
    class SwappyGrid;

    class Tile : public cocos2d::Sprite {

    public:
        bool init() override;
        void update(float delta) override;

        CREATE_FUNC(Tile);

        std::string getSpriteName();
        void setSpriteName(std::string name);
        void setGrid(SwappyGrid* pGrid);
        SwappyGrid* getGrid();
        void initOptions();
        void addEvents();

    protected:
        std::string spriteName;
        SwappyGrid* m_pSwappyGrid;

        cocos2d::Vec2 getSwapVec(cocos2d::Touch *pTouch);
    };
}

#endif //LORAFEL_TILE_H
