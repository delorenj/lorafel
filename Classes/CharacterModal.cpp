//
// Created by Jarad DeLorenzo on 6/15/16.
//

#include "CharacterModal.h"

using namespace lorafel;

bool CharacterModal::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }
    /**
     * Get the visible screen size
     */
    m_visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    m_origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    /**
     * Create the main window
     * Set the anchor point to the center
     * set the position to the origin of the parent
     */
    m_pWindow = cocos2d::Sprite::create("modal-m.png");
    m_pWindow->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    m_pWindow->setPosition(0, 0);

    /**
     * Set the parent node to center anchor
     * Set the parent node position to center of screen
     * Add the main window to the parent container
     */
    setAnchorPoint(cocos2d::Vec2(0, 0));
    setContentSize(m_pWindow->getContentSize());
    setPosition(m_origin.x + m_visibleSize.width/2, m_origin.y + m_visibleSize.height/2);
    addChild(m_pWindow);

    /**
     * Create the close button
     */
    m_pClose = cocos2d::Sprite::createWithSpriteFrameName("close-modal-x.png");
    m_pClose->setAnchorPoint(cocos2d::Vec2(1,1));
    m_pClose->setPosition(m_pWindow->getContentSize().width+m_pClose->getContentSize().width/4, m_pWindow->getContentSize().height+m_pClose->getContentSize().height/4);
    m_pWindow->addChild(m_pClose);

    auto closeListener = cocos2d::EventListenerTouchOneByOne::create();
    closeListener->onTouchBegan = CC_CALLBACK_2([=](cocos2d::Touch* touch, cocos2d::Event* event) {
      CCLOG("hi");
    });
    m_pClose->getEventDispatcher()->addEventListenerWithFixedPriority(closeListener, 1);

    return true;
}

CharacterModal* CharacterModal::createAndDropIn(cocos2d::Node* container) {
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto modal = CharacterModal::create();
    modal->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height + modal->getContentSize().height/2);
    auto moveTo = cocos2d::MoveTo::create(0.5f, cocos2d::Vec2(modal->getPosition().x, origin.y + visibleSize.height/2));
    auto ease = cocos2d::EaseBackOut::create(moveTo->clone());
    auto seq = cocos2d::Sequence::create(ease, NULL);
    container->addChild(modal);
    modal->runAction(seq);

    return modal;
}

cocos2d::Sprite* CharacterModal::getWindow() {
    return m_pWindow;
}





