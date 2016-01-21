//
//  TestScene.h
//
//
//  Created by Jarad DeLorenzo.
//
//

#ifndef ____TestScene____
#define ____TestScene____

#include "cocos2d.h"
#include "SwappyGrid.h"
#include "StateMachine.h"
#include "GridUI.h"

USING_NS_CC;

class GridUI;
class TestScene : public Node {

public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(TestScene);
    void setPhysicsWorld(PhysicsWorld* world){m_world = world;}

protected:
    Sprite* pSprBackground;
    lorafel::SwappyGrid* swappyGrid;
    PhysicsWorld* m_world;
    lorafel::StateMachine* m_pGameStateMachine;
    lorafel::GridUI *m_pGridUI;
    void initStateMachine();
};

#endif /* defined(____TestScene____) */