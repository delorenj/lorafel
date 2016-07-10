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

    m_pItemGrid = InventoryItemGrid::create(this);
    m_pItemGrid->setGlobalZOrder(LayerOrder::MODAL+1);
    m_pItemGrid->setAnchorPoint(cocos2d::Vec2(0.5f,1));
    m_pItemGrid->setPosition(getContentSize().width/2, getContentSize().height - getContentSize().height*0.176f);
    addChild(m_pItemGrid);

    return true;
}

void InventoryModal::update(float delta) {
}

