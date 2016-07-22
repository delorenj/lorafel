//
// Created by Jarad DeLorenzo on 7/20/16.
//

#include "InventoryEquipGrid.h"
#include "Player.h"

using namespace lorafel;

bool InventoryEquipGrid::init(cocos2d::Node* container) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    /**
     * Create the background of the
     * grid container
     */
    initWithFile("equip-slot-container.png");

    /**
     * Initialize each equip slot
     */
    auto pad = getContentSize().width * 0.014f;

    m_pItemSlotBody = EquipItemSlot::create();
    m_pItemSlotBody->setEquipMask(Player::BODY);
    m_pItemSlotBody->setPosition(cocos2d::Vec2(getContentSize().width/2, getContentSize().height/2));
    addChild(m_pItemSlotBody);
    auto wh = m_pItemSlotBody->getContentSize().width;

    m_pItemSlotLH = EquipItemSlot::create();
    m_pItemSlotLH->setEquipMask(Player::LEFT_HAND);
    m_pItemSlotLH->setPosition(m_pItemSlotBody->getPositionX() - wh - pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotLH);

    m_pItemSlotRH = EquipItemSlot::create();
    m_pItemSlotRH->setEquipMask(Player::RIGHT_HAND);
    m_pItemSlotRH->setPosition(m_pItemSlotBody->getPositionX() + wh + pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotRH);

    return true;

}

