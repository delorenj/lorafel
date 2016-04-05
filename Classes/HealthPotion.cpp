//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "HealthPotion.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"
#include "HealthPotionPlayerMove.h"
#include "Level.h"

using namespace lorafel;

bool HealthPotion::init(double amount) {
    if(!Consumable::init()) {
        return false;
    }

    m_amount = amount;
    initWithSpriteFrameName("PoisonGlyph.png");
    return true;
}

void HealthPotion::addEvents(cocos2d::Node* pNode) {
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
            use(PlayerManager::getInstance()->getPlayer()->getTile());
            removeFromParentAndCleanup(true);
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void HealthPotion::use(Tile* pTarget) {
    /**
     * If amount is less than 1, then consider it
     * a percentage of max health.
     *
     * If greater than 1, then consider it a flat
     * increase amount
     */
    int toIncreaseBy = 0;
    auto player = PlayerManager::getInstance()->getPlayer();

    if(m_amount <= 1) {
        toIncreaseBy = player->getMaxHp() * m_amount;
    } else {
        toIncreaseBy = m_amount;
    }

    HealthPotionPlayerMove* playerMove = new HealthPotionPlayerMove(m_pSwappyGrid, toIncreaseBy, pTarget);
    if(playerMove->isValid()) {
        m_pSwappyGrid->executePlayerMove(playerMove);
    }

}
