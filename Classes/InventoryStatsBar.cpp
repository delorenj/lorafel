//
// Created by Jarad M DeLorenzo on 1/10/17.
//

#include <cocos/2d/CCNode.h>
#include "InventoryStatsBar.h"
#include "StringPatch.h"
#include "PlayerManager.h"

using namespace lorafel;

bool InventoryStatsBar::init(cocos2d::Node *container) {
    if(!cocos2d::Node::init()) {
        return false;
    }

//    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    m_pContainer = container;
    
    auto height = container->getContentSize().width * 0.069f;
    auto width = container->getContentSize().width;
    CCLOG("StatsBar | Width=%f, Height=%f", width, height);
    /**
     * Create the background of the
     * grid container
     */
    auto bg = cocos2d::DrawNode::create();
    cocos2d::Vec2 rect[4];
    rect[0] = cocos2d::Vec2(0, 0);
    rect[1] = cocos2d::Vec2(width, 0);
    rect[2] = cocos2d::Vec2(width, height);
    rect[3] = cocos2d::Vec2(0, height);
    cocos2d::Color4F bgColor(121,118,118,1);
    bg->drawPolygon(rect, 4, bgColor, 0, bgColor);
    bg->setGlobalZOrder(LayerOrder::MODAL+2);
    addChild(bg);

    auto player = PlayerManager::getInstance()->getPlayer();

    
    /**
     * Create and position the stat labels
     * and their values
     */
    createStatLabel(m_pStr, m_pStrVal, "Str", player->getHitAmount(nullptr), 0.029f);
    createStatLabel(m_pDef, m_pDefVal, "Def", player->getDefAmount(nullptr), 0.208f);
    createStatLabel(m_pInt, m_pIntVal, "Int", player->getIntAmount(), 0.410f);
    createStatLabel(m_pHit, m_pHitVal, "Hit", 0, 0.609f);
    createStatLabel(m_pMov, m_pMovVal, "Mov", 0, 0.825f);
    
    return true;
}

void InventoryStatsBar::createStatLabel(cocos2d::Label *statNameLabel, cocos2d::Label *statValLabel, const std::string statName, int val, float xPosPercent) {
    auto statString = statName + ":";
    statNameLabel = cocos2d::Label::createWithTTF(statString.c_str(), "fonts/BebasNeue Bold.ttf", 28);
    statNameLabel->setAnchorPoint(Vec2(0,0));
    statNameLabel->setPosition(Vec2(m_pContainer->getContentSize().width * xPosPercent,0));
    statNameLabel->setGlobalZOrder(LayerOrder::MODAL+3);
    addChild(statNameLabel);

    statValLabel = cocos2d::Label::createWithTTF(to_string(val), "fonts/BebasNeue Bold.ttf", 28);
    statValLabel->setAnchorPoint(Vec2(0,0));
    statValLabel->setPosition(Vec2(statNameLabel->getPositionX() + +statNameLabel->getContentSize().width + statNameLabel->getContentSize().width * 0.19f, 0));
    statValLabel->setGlobalZOrder(LayerOrder::MODAL+3);
    addChild(statValLabel);
}

void InventoryStatsBar::setStat(const std::string stat, int val) {
    cocos2d::Label* label;

    if(stat == "str") {
        label = m_pStrVal;
    } else if(stat == "int") {
        label = m_pIntVal;
    } else if(stat == "def") {
        label = m_pDefVal;
    } else if(stat == "dex") {
        label = m_pHitVal;
    } else if(stat == "mov") {
        label = m_pMovVal;
    } else {
        CCLOG("InventoryStatsBar::setStat() - Invalid stat '%s'", stat.c_str());
        return;
    }
    label->setString(to_string(val));
}
