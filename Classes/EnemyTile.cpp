//
//  EnemyTile.cpp
//  Lorafel
//
//  Created by Jarad DeLorenzo on 1/25/16.
//
//

#include "EnemyTile.h"
#include "Globals.h"

using namespace lorafel;

bool EnemyTile::init() {
    // Add event listener for onHit()
    setTag(Tag::ENEMY);
    auto _listenter = cocos2d::EventListenerCustom::create("enemy_damaged", CC_CALLBACK_1(EnemyTile::onHit, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listenter, this);
}
