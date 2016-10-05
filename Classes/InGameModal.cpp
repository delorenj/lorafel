//
// Created by Jarad DeLorenzo on 6/15/16.
//

#include "InGameModal.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "InventoryModal.h"
#include "ItemDetailWindowFactory.h"

using namespace lorafel;

bool InGameModal::init() {
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
    initWithFile("modal-bg.png");
    setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    setPosition(m_origin.x + m_visibleSize.width/2, m_origin.y + m_visibleSize.height + getContentSize().height/2);
    setGlobalZOrder(LayerOrder::MODAL);

    /**
     * Create the close button
     */
    m_pClose = cocos2d::Sprite::createWithSpriteFrameName("close-modal-x.png");
    m_pClose->setAnchorPoint(cocos2d::Vec2(1,1));
    m_pClose->setPosition(getContentSize().width - m_pClose->getContentSize().width*0.21f, getContentSize().height - m_pClose->getContentSize().height*0.21f);
    m_pClose->setGlobalZOrder(LayerOrder::MODAL+1);
    addChild(m_pClose);

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

            ItemDetailWindowFactory::getInstance()->destroyExistingWindows();
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

InGameModal* InGameModal::createAndDropIn(cocos2d::Node* container) {
    /**
     * Always drop in the modal with the Inventory
     * screen first
     */
    auto modal = InventoryModal::create();

    container->addChild(modal, LayerOrder::MODAL);

    modal->loadInventory([&](int res) {
        CCLOG("InGameModal::loadInventoryCallback - Done Loading from Firebase with result %d =D", res);
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        auto modal = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("InventoryModal");
        modal->setPosition(cocos2d::Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y));
        auto moveTo = cocos2d::MoveTo::create(0.5f, cocos2d::Vec2(modal->getPosition().x, origin.y + visibleSize.height/2));
        auto ease = cocos2d::EaseBackOut::create(moveTo->clone());
        auto seq = cocos2d::Sequence::create(ease, NULL);
        modal->runAction(seq);
        GameStateMachine::getInstance()->setState<CharacterModalState>();
    });

    /**
     * Set game state to modal
     */
    GameStateMachine::getInstance()->pushState();
    GameStateMachine::getInstance()->setState<LoadingState>();

    return modal;
}

void InGameModal::dismiss(std::function<void(void)> callback) {
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

cocos2d::Sprite* InGameModal::createButton(const char* imageName, int index) {
    index -= 1;
    auto btn = cocos2d::Sprite::createWithSpriteFrameName("modal-nav-btn.png");
    btn->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    btn->setPosition(
            DISTRIBUTE(index, NAV_BUTTONS.size(), getContentSize().width),
            btn->getContentSize().height/2 + btn->getContentSize().height*0.126f
    );
    auto image = cocos2d::Sprite::createWithSpriteFrameName(imageName);
    image->setPosition(btn->getContentSize().width/2, btn->getContentSize().height/2);
    image->setGlobalZOrder(LayerOrder::MODAL+2);
    btn->addChild(image);
    btn->setGlobalZOrder(LayerOrder::MODAL+1);
    addChild(btn, LayerOrder::MODAL+1);
    return btn;
}









