//
// Created by Jarad DeLorenzo on 2/3/16.
//

#include "HeroTile.h"
#include "EventDataFloatie.h"
#include "Globals.h"

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
