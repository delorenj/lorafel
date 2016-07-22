//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "HealthPotion.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"
#include "HealthPotionPlayerMove.h"

using namespace lorafel;

bool HealthPotion::init(double amount) {
    if(!Consumable::init()) {
        return false;
    }

    m_amount = amount;
    m_itemName = getItemName();
    addEquipMask(Player::CONSUMABLE);
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

bool HealthPotion::addToInventory() {
    auto inventory = PlayerManager::getInstance()->getPlayer()->getInventory();
    inventory->addItem(this);
    _eventDispatcher->dispatchCustomEvent("itemAdded", this);
}

const char* HealthPotion::getItemName() const {
    /**
     * This is a percentage-based potion
     */
    if(m_amount <= 0.1) {
        return "Stupid Potion";
    } else if(m_amount <= 0.2) {
        return "Yummy Potion";
    } else if(m_amount <= 0.5) {
        return "Awesome Potion";
    } else if(m_amount <= 0.8) {
        return "Damn Good Potion";
    } else if(m_amount <= 1) {
            return "Grand Potion";
    } else {
        /**
         * This is a flat-amount potion
         */
        return std::string("Health Potion " + to_string(m_amount)).c_str();
    }
}


