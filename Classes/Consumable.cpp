//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "Consumable.h"
#include "Globals.h"
#include "GameStateMachine.h"
#include "SwappyGridScene.h"

using namespace lorafel;

void Consumable::use(lorafel::Tile* pTarget) {

}

bool Consumable::init() {
    if(!Item::init()) {
        return false;
    }
    setTag(Tag::CONSUMABLE);
    return true;
}

void Consumable::addEvents(cocos2d::Node* pNode) {
    m_pSwappyGrid = static_cast<SwappyGrid*>(pNode);

    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->isBusy()) {
            return false;
        }

        cocos2d::Vec2 p = convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = getBoundingBox();
        m_pSwappyGrid->setCurrentTouchId(touch->_ID);

        if(rect.containsPoint(p))
        {
            CCLOG("Touched me 8==D");
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        CCLOG("You stopped touch me 8=====D");
    };

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Consumable::equip(EquipItemSlot* pSlot) {
    Item::equip(pSlot);
}
