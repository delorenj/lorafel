//
// Created by Jarad DeLorenzo on 7/9/16.
//

#include "InventoryModal.h"
#include "Globals.h"
#include "sqlite3.h"

using namespace lorafel;

bool InventoryModal::init() {
    if(!InGameModal::init()) {
        return false;
    }

    sqlite3 *db;
    auto rc = sqlite3_open("test.db", &db);

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

void InventoryModal::update(float delta) {
}

