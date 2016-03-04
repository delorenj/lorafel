//
// Created by Jarad DeLorenzo on 3/3/16.
//

#ifndef LORAFEL_SWAPPYGRIDSCENE_H
#define LORAFEL_SWAPPYGRIDSCENE_H

#include "cocos2d.h"
#include "SwappyGrid.h"
#include "StateMachine.h"
#include "GridUI.h"
#include "GridTestUI.h"
#include "Level.h"

namespace lorafel {
    class GridUI;
    class SwappyGridScene : public cocos2d::Node {
    public:
        virtual bool init() override;
        virtual ~SwappyGridScene();

    protected:
        cocos2d::Sprite* m_pBackground;
        SwappyGrid* m_pSwappyGrid;
        cocos2d::PhysicsWorld* m_world;
        StateMachine* m_pGameStateMachine;
        GridUI *m_pGridUI;
        Level* m_pLevel;

    };
}

#endif //LORAFEL_SWAPPYGRIDSCENE_H
