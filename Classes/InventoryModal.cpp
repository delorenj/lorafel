//
// Created by Jarad DeLorenzo on 7/9/16.
//

#include "InventoryModal.h"
#include "Globals.h"

using namespace lorafel;

bool InventoryModal::init() {
    if(!InGameModal::init()) {
        return false;
    }

    setName("InventoryModal");
    setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));

    m_pItemGrid = InventoryItemGrid::create(this);
    m_pItemGrid->setGlobalZOrder(LayerOrder::MODAL+1);
    m_pItemGrid->setAnchorPoint(cocos2d::Vec2(0.5f,1));
    m_pItemGrid->setPosition(getContentSize().width/2, getContentSize().height - getContentSize().height*0.176f);
    addChild(m_pItemGrid);

    m_pEquipGrid = InventoryEquipGrid::create(this);
    m_pEquipGrid->setGlobalZOrder(LayerOrder::MODAL+1);
    m_pEquipGrid->setAnchorPoint(cocos2d::Vec2(0.5f,1));
    m_pEquipGrid->setPosition(getContentSize().width/2, getContentSize().height - getContentSize().height*0.493);
    addChild(m_pEquipGrid);

    return true;
}

void InventoryModal::readyCheck(float dt) {
    if(m_pItemGrid->isInitialized()) {// && m_pEquipGrid->isInitialized()) {
        CCLOG("InventoryModal::readyCheck() - initialized !");
        m_pItemGrid->setInitialized(false);
        m_pEquipGrid->setInitialized(false);
        m_callback(1);
        unschedule(schedule_selector(InventoryModal::readyCheck));
    }
}

