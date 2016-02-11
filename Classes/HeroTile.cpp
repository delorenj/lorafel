//
// Created by Jarad DeLorenzo on 2/3/16.
//

#include "HeroTile.h"
#include "EventDataFloatie.h"
#include "Globals.h"
#include "GameStateMachine.h"
#include "BasicPlayerMove.h"

using namespace lorafel;

HeroTile* HeroTile::create(const char string[100]){
    HeroTile* sprite = new HeroTile();
    sprite->init();
    if (sprite->initWithSpriteFrameName(string))
    {
        sprite->setTileName("Hero");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        sprite->setTag(Tag::HERO);
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}

bool HeroTile::init() {
    // Add event listener for onHit()
    auto _listenter = cocos2d::EventListenerCustom::create("hero_damaged", CC_CALLBACK_1(HeroTile::onHit, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listenter, this);
}

void HeroTile::applyHit(Match* pMatch) {
    //TODO
//    auto primaryTile = pMatch->getPrimaryTile();
//    bool isStackable = primaryTile->isStackable();
//    int hitAmount = primaryTile->getRandHit(this);
//    if(isStackable) {
//        hitAmount *= (pMatch->getTileSetSize() - pMatch->getNumEnemies());
//    }
//
//    decreaseHpBy(hitAmount);
//
//    // Fire off an Hit event
//    cocos2d::EventCustom e("hero_damaged");
//    EventData* val = new EventDataFloatie(hitAmount, getGrid()->convertToWorldSpace(TILE_CENTER) + cocos2d::Vec2(0,40));
//    e.setUserData(val);
//    _eventDispatcher->dispatchEvent(&e);
//    auto particle = cocos2d::ParticleSystemQuad::create("green_dust.plist");
//    particle->setAutoRemoveOnFinish(true);
//    particle->setPosition(TILE_CENTER);
//    m_pSwappyGrid->addChild(particle);
//    CC_SAFE_DELETE(val);
//
//    if(m_hp <= 0) {
//        //game over
//        remove();
//    }

}

void HeroTile::onHit(cocos2d::EventCustom* event) {
    EventDataFloatie* data = static_cast<EventDataFloatie*>(event->getUserData());

    CCLOG("Hit for %d HP", data->val);
}

void HeroTile::onMatch(Match *pMatch) {
    applyHit(pMatch);
}

void HeroTile::decreaseHpBy(int amount) {
    m_hp -= amount;
}

void HeroTile::remove() {
    auto particle = cocos2d::ParticleExplosion::create();
    particle->setAutoRemoveOnFinish(true);
    particle->setScale(1);
    particle->setTotalParticles(1500);
    particle->setDuration(0.2);
    particle->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(particle);
    setVisible(false);
    m_pSwappyGrid->addTileToRemoveQueue(static_cast<Tile*>(this));

}

void HeroTile::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->isBusy()) {
            return false;
        }

        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = this->getBoundingBox();
        m_pSwappyGrid->setCurrentTouchId(touch->_ID);

        if(rect.containsPoint(p))
        {
            GameStateMachine::getInstance()->enterState<TileTouchStartState>();
            auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTouchStartPos(p);
            touchState->setTileStartPos(getPosition());
            TileList* validMoves = new TileList();
            validMoves->push_back(getTop());
            validMoves->push_back(getLeft());
            validMoves->push_back(getRight());
            m_pSwappyGrid->highlightTiles(validMoves);
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if("TileTouchStartState" == touchState->getName()) {
            auto tilePos = touchState->getTileStartPos();
            auto touchPos = touchState->getTouchStartPos();
            GameStateMachine::getInstance()->enterState<TileTouchMoveState>();
            touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTileStartPos(tilePos);
            touchState->setTouchStartPos(touchPos);
        }
        if("TileTouchMoveState" == touchState->getName()) {
            cocos2d::Vec2 delta = _parent->convertToNodeSpace(touch->getLocation()) - touchState->getTouchStartPos();
            setPosition(touchState->getTileStartPos().x + delta.x, touchState->getTileStartPos().y + delta.y);
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        m_pSwappyGrid->getChildByTag(Tag::HIGHLIGHT)->removeFromParentAndCleanup(true);
        if(touchState->getName() == "TileTouchMoveState") {
            GameStateMachine::getInstance()->enterState<IdleState>();
            auto move = cocos2d::MoveTo::create(0.2, touchState->getTileStartPos());
            runAction(move);
        } else if(touchState->getName() == "TileTouchStartState") {
            GameStateMachine::getInstance()->enterState<IdleState>();
        }
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
