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
//    createStatLabel(m_pStr, m_pStrVal, "Str", 0, 0.029f);

    m_pDef = cocos2d::Label::createWithTTF("Def:", "fonts/BebasNeue Bold.ttf", 28);
    m_pDef->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pDef->setPosition(cocos2d::Vec2(width*0.208f,0));
    m_pDef->setGlobalZOrder(LayerOrder::MODAL+3);
    addChild(m_pDef);

    m_pDefVal = cocos2d::Label::createWithTTF(to_string(player->getDef()), "fonts/BebasNeue Bold.ttf", 28);
    m_pDefVal->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pDefVal->setPosition(cocos2d::Vec2(m_pDef->getPositionX() + +m_pDef->getContentSize().width + m_pDef->getContentSize().width * 0.19f, 0));
    m_pDefVal->setGlobalZOrder(LayerOrder::MODAL+3);
    addChild(m_pDefVal);

    return true;
}

void InventoryStatsBar::createStatLabel(cocos2d::Label *statNameLabel, cocos2d::Label *statValLabel, const std::string statName, int val, float xPosPercent) {
    auto statString = statName + ":";
    statNameLabel = cocos2d::Label::createWithTTF(statString.c_str(), "fonts/BebasNeue Bold.ttf", 28);
    statNameLabel->setAnchorPoint(Vec2(0,0));
    statNameLabel->setPosition(Vec2(_parent->getContentSize().width * xPosPercent,0));
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
        label = m_pDexVal;
    } else if(stat == "mov") {
        label = m_pMovVal;
    } else {
        CCLOG("InventoryStatsBar::setStat() - Invalid stat '%s'", stat.c_str());
        return;
    }
    label->setString(to_string(val));
}
