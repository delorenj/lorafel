//
// Created by Jarad DeLorenzo on 3/1/16.
//

#include <cocos/ui/UIText.h>
#include "GameOverUI.h"
#include "Globals.h"

using namespace lorafel;

bool GameOverUI::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }

    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    m_pLayout = cocos2d::ui::Layout::create();
    m_pLayout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
    m_pLayout->setAnchorPoint(cocos2d::Vec2(0, 0));
    m_pLayout->setPosition(origin);
    m_pLayout->setContentSize(visibleSize);
    m_pLayout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pLayout->setBackGroundColor(cocos2d::Color3B(0,0,0));
    m_pLayout->setBackGroundColorOpacity(100);
    m_pLayout->setName("m_pLayout");

    setCascadeOpacityEnabled(true);
    setOpacity(0);

    addChild(m_pLayout);
    return true;
}

void GameOverUI::show() {
    auto director = cocos2d::Director::getInstance();
    setPosition(director->getVisibleOrigin());
    director->getRunningScene()->addChild(this, lorafel::LayerOrder::GAMEOVER);
    runAction(cocos2d::Sequence::create(
            cocos2d::FadeIn::create(0.25f),
            cocos2d::CallFunc::create(CC_CALLBACK_0(GameOverUI::tweenText, this)),
            cocos2d::DelayTime::create(0.4f),
            cocos2d::CallFunc::create(CC_CALLBACK_0(GameOverUI::showButtons, this)),
            NULL)
    );

}

void GameOverUI::tweenText() {
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto size = cocos2d::Director::getInstance()->getVisibleSize();
    m_gameOverText = cocos2d::ui::Text::create("GAME OVER", "fonts/BebasNeue Bold.ttf", 120);

    m_gameOverText->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    auto gameOverToPos = cocos2d::Vec2(origin.x + size.width/2, origin.y + size.height/2);
    m_gameOverText->setPosition(cocos2d::Vec2(origin.x + size.width/2, origin.y + size.height+ m_gameOverText->getContentSize().height));
    m_gameOverText->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, gameOverToPos)));
    addChild(m_gameOverText);

}

void GameOverUI::showButtons() {
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto size = cocos2d::Director::getInstance()->getVisibleSize();
    auto center = cocos2d::Vec2(origin.x + size.width/2, origin.y + size.height/2);

    m_tryAgainButton = cocos2d::ui::Button::create("try_again_button.png","try_again_button_pressed.png");
    m_tryAgainButton->setAnchorPoint(cocos2d::Vec2(0.5,1));
    auto tryAgainToPos = cocos2d::Vec2(center.x, center.y - m_gameOverText->getContentSize().height/2 - 10);
    m_tryAgainButton->setPosition(tryAgainToPos);
    m_tryAgainButton->setScale(0.1);
    m_tryAgainButton->setTitleText("Retry");
    m_tryAgainButton->runAction(cocos2d::EaseBackOut::create(cocos2d::ScaleTo::create(0.5f, 1.0f)));
    addChild(m_tryAgainButton);

    m_quitButton = cocos2d::ui::Button::create("quit_button.png","quit_button_pressed.png");
    m_quitButton->setAnchorPoint(cocos2d::Vec2(0.5,1));
    auto quitToPos = cocos2d::Vec2(center.x, m_tryAgainButton->getPosition().y - m_tryAgainButton->getContentSize().height - 10);
    m_quitButton->setPosition(quitToPos);
    m_quitButton->setScale(0.1);
    m_quitButton->setTitleText("Quit");
    m_quitButton->runAction(cocos2d::EaseBackOut::create(cocos2d::ScaleTo::create(0.5f, 1.0f)));
    addChild(m_quitButton);

}
