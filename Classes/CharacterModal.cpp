//
// Created by Jarad DeLorenzo on 6/15/16.
//

#include "CharacterModal.h"
#include "GameStateMachine.h"
#include "Globals.h"

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
    m_pWindow = cocos2d::Sprite::create("modal-bg.png");
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
    closeListener->setSwallowTouches(true);
    closeListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = m_pWindow->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = m_pClose->getBoundingBox();
        if(rect.containsPoint(p))
        {
            std::function<void(void)> callback = [&]() {
                removeFromParentAndCleanup(true);
                GameStateMachine::getInstance()->popState();
            };

            dismiss(callback);
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    m_pClose->getEventDispatcher()->addEventListenerWithSceneGraphPriority(closeListener, this);

    /**
     * Add the nav buttons on the footer
     */
    int buttonIndex = 0;
    int numNavButtons = 4;
    float modalWidth = m_pWindow->getContentSize().width;

    CCLOG("modal wid=%f", m_pWindow->getContentSize().width);

    m_pInventory = cocos2d::Sprite::createWithSpriteFrameName("satchel.png");
    m_pInventory->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    m_pInventory->setPosition(
            DISTRIBUTE(buttonIndex++, numNavButtons, modalWidth),
            m_pInventory->getContentSize().height/2 + m_pInventory->getContentSize().height*0.50f
    );
    m_pWindow->addChild(m_pInventory);

    m_pAchievements = cocos2d::Sprite::createWithSpriteFrameName("trophy.png");
    m_pAchievements->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    m_pAchievements->setPosition(
            DISTRIBUTE(buttonIndex++, numNavButtons, modalWidth),
            m_pInventory->getContentSize().height/2 + m_pInventory->getContentSize().height*0.50f
    );
    m_pWindow->addChild(m_pAchievements);

    m_pSettings = cocos2d::Sprite::createWithSpriteFrameName("gear.png");
    m_pSettings->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    m_pSettings->setPosition(
            DISTRIBUTE(buttonIndex++, numNavButtons, modalWidth),
            m_pInventory->getContentSize().height/2 + m_pInventory->getContentSize().height*0.50f
    );
    m_pWindow->addChild(m_pSettings);

    m_pStore = cocos2d::Sprite::createWithSpriteFrameName("store.png");
    m_pStore->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    m_pStore->setPosition(
            DISTRIBUTE(buttonIndex++, numNavButtons, modalWidth),
            m_pInventory->getContentSize().height/2 + m_pInventory->getContentSize().height*0.50f
    );
    m_pWindow->addChild(m_pStore);

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

    /**
     * Set game state to modal
     */
    GameStateMachine::getInstance()->pushState();
    GameStateMachine::getInstance()->setState<CharacterModalState>();

    return modal;
}

CharacterModal* CharacterModal::dismiss(std::function<void(void)> callback) {
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();


    auto moveTo = cocos2d::MoveTo::create(0.5f, cocos2d::Vec2(getPosition().x, origin.y + visibleSize.height + getContentSize().height/2));
    auto ease = cocos2d::EaseBackIn::create(moveTo->clone());

    auto onComplete = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        callback();
    });
    auto seq = cocos2d::Sequence::create(ease, onComplete, NULL);

    runAction(seq);
}





