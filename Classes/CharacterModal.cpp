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
    m_pWindow->setPosition(m_origin.x + m_visibleSize.width/2, m_origin.y + m_visibleSize.height + getContentSize().height/2);
    m_pWindow->setGlobalZOrder(LayerOrder::MODAL);
    addChild(m_pWindow);
    /**
     * Create the close button
     */
    m_pClose = cocos2d::Sprite::createWithSpriteFrameName("close-modal-x.png");
    m_pClose->setAnchorPoint(cocos2d::Vec2(1.0f,1.0f));
    m_pClose->setPosition(0,0);
    m_pWindow->addChild(m_pClose);
//    m_pClose->setGlobalZOrder(LayerOrder::MODAL+1);

    auto closeListener = cocos2d::EventListenerTouchOneByOne::create();
    closeListener->setSwallowTouches(true);
    closeListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 p = convertToNodeSpace(touch->getLocation());
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
    m_pInventory = createButton("satchel.png", 1);
    m_pAchievements = createButton("trophy.png", 2);
    m_pSettings = createButton("gear.png", 3);
    m_pStore = createButton("store.png", 4);
    return true;
}

CharacterModal* CharacterModal::createAndDropIn(cocos2d::Node* container) {
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto modal = CharacterModal::create();
    auto moveTo = cocos2d::MoveTo::create(0.5f, cocos2d::Vec2(modal->getPosition().x, origin.y + visibleSize.height/2));
    auto ease = cocos2d::EaseBackOut::create(moveTo->clone());
    auto seq = cocos2d::Sequence::create(ease, NULL);
    container->addChild(modal, LayerOrder::MODAL);
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

cocos2d::Sprite* CharacterModal::createButton(const char* imageName, int index) {
    index -= 1;
    auto btn = cocos2d::Sprite::createWithSpriteFrameName("modal-nav-btn.png");
    btn->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    btn->setPosition(
            DISTRIBUTE(index, NAV_BUTTONS.size(), getContentSize().width),
            btn->getContentSize().height/2 + btn->getContentSize().height*0.50f
    );
    auto image = cocos2d::Sprite::createWithSpriteFrameName(imageName);
    image->setPosition(btn->getContentSize().width/2, btn->getContentSize().height/2);
//    image->setGlobalZOrder(LayerOrder::MODAL+2);
    btn->addChild(image);
//    btn->setGlobalZOrder(LayerOrder::MODAL+1);
//    addChild(btn, LayerOrder::MODAL+1);
    return btn;
}







