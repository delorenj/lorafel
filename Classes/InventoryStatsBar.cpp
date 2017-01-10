//
// Created by Jarad M DeLorenzo on 1/10/17.
//

#include "InventoryStatsBar.h"
#include "Player.h"
#include "PlayerManager.h"

bool InventoryStatsBar::init(cocos2d::Node *container) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    /**
     * Create the background of the
     * grid container
     */
    initWithFile("equip-slot-container.png");
    setScaleY(0.18f);

    return true;
}
