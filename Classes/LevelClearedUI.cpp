//
// Created by Jarad M DeLorenzo on 11/21/16.
//

#include "LevelClearedUI.h"
#include "Globals.h"
#include "GameScene.h"
#include "LevelManager.h"

using namespace lorafel;

bool LevelClearedUI::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }

    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    m_pLayout = cocos2d::ui::Layout::create();
    m_pLayout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
    m_pLayout->setAnchorPoint(cocos2d::Vec2(0, 0));
    m_pLayout->setPosition(cocos2d::Vec2(0,0));
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

void LevelClearedUI::show() {
    auto director = cocos2d::Director::getInstance();
    this->setPosition(director->getVisibleOrigin());
    director->getRunningScene()->addChild(this, LayerOrder::GAMEOVER);
    runAction(cocos2d::Sequence::create(
            cocos2d::FadeIn::create(0.25f),
            cocos2d::CallFunc::create(CC_CALLBACK_0(LevelClearedUI::tweenText, this)),
            cocos2d::DelayTime::create(0.4f),
            cocos2d::CallFunc::create(CC_CALLBACK_0(LevelClearedUI::showButtons, this)),
            NULL)
    );

}

void LevelClearedUI::tweenText() {
    auto size = cocos2d::Director::getInstance()->getVisibleSize();
    m_pLevelCleared = cocos2d::Sprite::create("level_cleared.png");

    m_pLevelCleared->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    auto gameOverToPos = cocos2d::Vec2(size.width/2, size.height/2);
    m_pLevelCleared->setPosition(cocos2d::Vec2(size.width/2, size.height+ m_pLevelCleared->getContentSize().height));
    m_pLevelCleared->runAction(cocos2d::EaseBackOut::create(cocos2d::MoveTo::create(0.5f, gameOverToPos)));
    addChild(m_pLevelCleared);

}

void LevelClearedUI::showButtons() {
    auto size = cocos2d::Director::getInstance()->getVisibleSize();
    auto center = cocos2d::Vec2(size.width/2, size.height/2);

    m_tryAgainButton = cocos2d::ui::Button::create();
    m_tryAgainButton->loadTextures("try_again_button.png","try_again_button_pressed.png","", cocos2d::ui::Widget::TextureResType::PLIST);
    m_tryAgainButton->setAnchorPoint(cocos2d::Vec2(0.5,1));
    auto tryAgainToPos = cocos2d::Vec2(center.x, center.y - m_pLevelCleared->getContentSize().height/2 - 10);
    m_tryAgainButton->setPosition(tryAgainToPos);
    m_tryAgainButton->setScale(0.1);
    m_tryAgainButton->runAction(cocos2d::EaseBackOut::create(cocos2d::ScaleTo::create(0.5f, 1.0f)));

    m_tryAgainButton->addTouchEventListener(CC_CALLBACK_2(LevelClearedUI::tryAgain, this));

    addChild(m_tryAgainButton);

    m_nextButton= cocos2d::ui::Button::create();
    m_nextButton->loadTextures("next_level.png","next_level.png", "", cocos2d::ui::Widget::TextureResType::PLIST);
    m_nextButton->setAnchorPoint(cocos2d::Vec2(0.5,1));
    auto nextToPos = cocos2d::Vec2(center.x, m_tryAgainButton->getPosition().y - m_tryAgainButton->getContentSize().height - 10);
    m_nextButton->setPosition(nextToPos);
    m_nextButton->setScale(0.1);
    m_nextButton->runAction(cocos2d::EaseBackOut::create(cocos2d::ScaleTo::create(0.5f, 1.0f)));
    addChild(m_nextButton);

}

void LevelClearedUI::tryAgain(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType) {
    if(eventType == cocos2d::ui::Widget::TouchEventType::ENDED) {
        auto runningScene = cocos2d::Director::getInstance()->getRunningScene();
        auto lt = LevelManager::getInstance()->getLevelTree();
        auto levelRoot = lt->at("levels").asValueVector();
        auto levelConfig = levelRoot[1].asValueMap();
        runningScene->removeAllChildrenWithCleanup(true);
        auto newScene = GameScene::createScene(LevelManager::getInstance()->getCurrentLevel()->getLevelId());
        cocos2d::Director::getInstance()->replaceScene(
                cocos2d::TransitionFade::create(0.1, newScene, cocos2d::Color3B(0,0,0))
        );
    }
}
