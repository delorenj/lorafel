//
// Created by Jarad DeLorenzo on 1/19/16.
//

#include "XpUI.h"
#include "PlayerManager.h"
#include "String.h"

using namespace lorafel;

bool XpUI::init() {
    m_pPlayer = PlayerManager::getInstance()->getPlayer();
    m_pLevelMananger = m_pPlayer->getLevelManager();

    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto length = visibleSize.width * 0.40;

    cocos2d::Size size(length,length*0.18);
    setContentSize(size);

    auto layout = cocos2d::ui::Layout::create();
    layout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
    layout->setContentSize(size);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::NONE);
    layout->setBackGroundColor(cocos2d::Color3B(128, 128, 128));
    layout->setName("xpLayout");
    addChild(layout);

    auto lp = cocos2d::ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
    lp->setMargin(cocos2d::ui::Margin(0,3,0,8));
    m_pXpBar = cocos2d::ui::LoadingBar::create("xp_bar.png");
    m_pXpBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
    m_pXpBar->setLayoutParameter(lp);
    layout->addChild(m_pXpBar);

    lp = cocos2d::ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_LEFT_BOTTOM);
    m_pXpText = cocos2d::ui::Text::create("XP","fonts/BebasNeue Bold.ttf", 14);
    m_pXpText->setColor(cocos2d::Color3B::WHITE);
    m_pXpText->setLayoutParameter(lp);
    layout->addChild(m_pXpText);

    lp = cocos2d::ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_RIGHT_BOTTOM);
    m_pNextXpText = cocos2d::ui::Text::create("NEXT","fonts/BebasNeue Bold.ttf", 14);
    m_pNextXpText->setColor(cocos2d::Color3B::WHITE);
    m_pNextXpText->setLayoutParameter(lp);
    layout->addChild(m_pNextXpText);

    lp = cocos2d::ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
    lp->setMargin(cocos2d::ui::Margin(0,15,0,0));
    m_pLvlText = cocos2d::ui::Text::create("LVL","fonts/BebasNeue Bold.ttf", 28);
    m_pLvlText->setColor(cocos2d::Color3B::WHITE);
    m_pLvlText->setLayoutParameter(lp);
    layout->addChild(m_pLvlText);

    scheduleUpdate();
    return true;

}

void XpUI::update(float delta) {
    auto lm = m_pLevelMananger;
    m_pXpBar->setPercent(lm->getLevelUpInPercent());
    m_pXpText->setString(String::to_string<const unsigned long>(lm->getXp()) + " xp");
    m_pNextXpText->setString(String::to_string<const unsigned long>(lm->levelToXp(lm->getLevel()+1)) + " xp");
    m_pLvlText->setString("Level " + String::to_string<const int>(lm->getLevel()));
}
