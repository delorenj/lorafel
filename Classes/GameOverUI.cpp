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
            cocos2d::CallFunc::create(CC_CALLBACK_0(GameOverUI::showButtons, this)),
            NULL)
    );

}

void GameOverUI::tweenText() {
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto size = cocos2d::Director::getInstance()->getVisibleSize();
    m_gameOverText = cocos2d::ui::Text::create("GAME OVER", "fonts/BebasNeue Bold.ttf", 120);
    m_tryAgainText = cocos2d::ui::Text::create("TRY AGAIN", "fonts/BebasNeue Regular.ttf", 60);
    m_quitText = cocos2d::ui::Text::create("QUIT", "fonts/BebasNeue Regular.ttf", 60);

    m_gameOverText->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    auto gameOverToPos = cocos2d::Vec2(origin.x + size.width/2, origin.y + size.height/2);
    m_gameOverText->setPosition(cocos2d::Vec2(origin.x + size.width/2, origin.y + size.height+ m_gameOverText->getContentSize().height));
    m_gameOverText->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, gameOverToPos)));
    addChild(m_gameOverText);

    m_tryAgainText->setAnchorPoint(cocos2d::Vec2(0,1));
    auto tryAgainToPos = cocos2d::Vec2(gameOverToPos.x- m_gameOverText->getContentSize().width/2, gameOverToPos.y - m_gameOverText->getContentSize().height - 10);
    m_tryAgainText->setPosition(cocos2d::Vec2(gameOverToPos.x- m_gameOverText->getContentSize().width/2, origin.y + size.height+ m_tryAgainText->getContentSize().height));
    m_tryAgainText->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, tryAgainToPos)));
    addChild(m_tryAgainText);

    m_quitText->setAnchorPoint(cocos2d::Vec2(1,1));
    auto quitToPos = cocos2d::Vec2(gameOverToPos.x+ m_gameOverText->getContentSize().width/2, gameOverToPos.y - m_gameOverText->getContentSize().height - 10);
    m_quitText->setPosition(cocos2d::Vec2(gameOverToPos.x+ m_gameOverText->getContentSize().width/2, origin.y + size.height+ m_quitText->getContentSize().height));
    m_quitText->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, quitToPos)));
    addChild(m_quitText);

}

void GameOverUI::showButtons() {
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto size = cocos2d::Director::getInstance()->getVisibleSize();

    m_tryAgainButton = cocos2d::ui::Button::create("try_again_button.png");
    m_tryAgainButton->setAnchorPoint(cocos2d::Vec2(0,1));
    auto tryAgainToPos = cocos2d::Vec2(m_gameOverText->getPosition().x - m_gameOverText->getContentSize().width/2, m_gameOverText->getPosition().y - m_gameOverText->getContentSize().height);
    m_tryAgainButton->setPosition(tryAgainToPos);
    m_tryAgainButton->setScale(0);
    m_tryAgainButton->setTitleText("Retry");
    m_tryAgainButton->runAction(cocos2d::EaseBackOut::create(cocos2d::ScaleTo::create(0.2f, 1)));
    addChild(m_tryAgainButton);

    m_quitButton = cocos2d::ui::Button::create("quit_button.png");
    m_quitButton->setAnchorPoint(cocos2d::Vec2(1,1));
    auto quitToPos = cocos2d::Vec2(m_gameOverText->getPosition().x + m_gameOverText->getContentSize().width/2, m_gameOverText->getPosition().y - m_gameOverText->getContentSize().height);
    m_quitButton->setPosition(quitToPos);
    m_quitButton->setScale(0);
    m_quitButton->setTitleText("Quit");
    m_tryAgainButton->runAction(cocos2d::EaseBackOut::create(cocos2d::ScaleTo::create(0.2f, 1)));
    addChild(m_quitButton);

}
