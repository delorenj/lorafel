//
// Created by Jarad M DeLorenzo on 1/10/17.
//

#include "InventoryStatsBar.h"
#include "StringPatch.h"
#include "PlayerManager.h"

using namespace lorafel;

bool InventoryStatsBar::init(cocos2d::Node *container) {
    if(!cocos2d::Node::init()) {
        return false;
    }

//    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    /**
     * Create the background of the
     * grid container
     */
    auto bg = cocos2d::DrawNode::create();
    cocos2d::Vec2 rect[4];
    rect[0] = cocos2d::Vec2(0, 0);
    rect[1] = cocos2d::Vec2(container->getContentSize().width, 0);
    rect[2] = cocos2d::Vec2(container->getContentSize().width, 50);
    rect[3] = cocos2d::Vec2(0, 50);
    cocos2d::Color4F white(0.8f,0.8f,0.8f,1);
    bg->drawPolygon(rect, 4, white, 1, white);
    bg->setGlobalZOrder(LayerOrder::MODAL+2);
    bg->setPosition(cocos2d::Vec2(-container->getContentSize().width/2, 25));
    addChild(bg);

    auto player = PlayerManager::getInstance()->getPlayer();

    /**
     * Create and position the stat labels
     * and their values
     */
    m_pStr = cocos2d::Label::createWithTTF("Str:", "fonts/BebasNeue Bold.ttf", 28);
    m_pStr->setPosition(cocos2d::Vec2(0,0));
    m_pStr->setGlobalZOrder(LayerOrder::MODAL+2);
    addChild(m_pStr);

    m_pStrVal = cocos2d::Label::createWithTTF(to_string(player->getStr()), "fonts/BebasNeue Bold.ttf", 28);
    m_pStrVal->setPosition(cocos2d::Vec2(m_pStr->getPositionX() + m_pStr->getContentSize().width + 5, 0));
    m_pStrVal->setGlobalZOrder(LayerOrder::MODAL+2);
    addChild(m_pStrVal);

    return true;
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
