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
            NULL)
    );

}

void GameOverUI::tweenText() {
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto size = cocos2d::Director::getInstance()->getVisibleSize();
    auto gameOver = cocos2d::ui::Text::create("GAME OVER", "fonts/BebasNeue Bold.ttf", 120);
    auto tryAgain = cocos2d::ui::Text::create("TRY AGAIN", "fonts/BebasNeue Regular.ttf", 60);
    auto quit = cocos2d::ui::Text::create("QUIT", "fonts/BebasNeue Regular.ttf", 60);

    gameOver->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    auto gameOverToPos = cocos2d::Vec2(origin.x + size.width/2, origin.y + size.height/2);
    gameOver->setPosition(cocos2d::Vec2(origin.x + size.width/2, origin.y + size.height+gameOver->getContentSize().height));
    gameOver->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, gameOverToPos)));
    addChild(gameOver);

    tryAgain->setAnchorPoint(cocos2d::Vec2(0,1));
    auto tryAgainToPos = cocos2d::Vec2(gameOverToPos.x-gameOver->getContentSize().width/2, gameOverToPos.y - gameOver->getContentSize().height - 10);
    tryAgain->setPosition(cocos2d::Vec2(gameOverToPos.x-gameOver->getContentSize().width/2, origin.y + size.height+tryAgain->getContentSize().height));
    tryAgain->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, tryAgainToPos)));
    addChild(tryAgain);

    quit->setAnchorPoint(cocos2d::Vec2(1,1));
    auto quitToPos = cocos2d::Vec2(gameOverToPos.x+gameOver->getContentSize().width/2, gameOverToPos.y - gameOver->getContentSize().height - 10);
    quit->setPosition(cocos2d::Vec2(gameOverToPos.x+gameOver->getContentSize().width/2, origin.y + size.height+quit->getContentSize().height));
    quit->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, quitToPos)));
    addChild(quit);

}
