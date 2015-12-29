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

USING_NS_CC;

class TestScene : public Node {

public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(TestScene);
    void setPhysicsWorld(PhysicsWorld* world){m_world = world;}
    lorafel::StateMachine* getStateMachine() { return m_pStateMachine; }

protected:
    Sprite* pSprBackground;
    lorafel::SwappyGrid* swappyGrid;
    PhysicsWorld* m_world;
    lorafel::StateMachine* m_pStateMachine;

    void initStateMachine();
};

#endif /* defined(____TestScene____) */