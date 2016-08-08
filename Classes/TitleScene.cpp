//
// Created by Jarad DeLorenzo on 8/7/16.
//

#include "TitleScene.h"
#include "Globals.h"
#include "FirebaseAuth.h"
#include "TestScene.h"
#include "NDKHelper/NDKHelper.h"

using namespace lorafel;

cocos2d::Scene* TitleScene::createScene() {
    auto scene = cocos2d::Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }

    // Set the Authentication state machine
    m_pStateMachine = AuthStateMachine::getInstance();
    m_pStateMachine->setState<LoggedOutState>();

    // Set the background
    m_pBackground = cocos2d::Sprite::create("title-bg.png");

    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    CCLOG("visibleSize: (%f,%f)", visibleSize.width, visibleSize.height);
    CCLOG("bg size: (%f,%f)", m_pBackground->getContentSize().width, m_pBackground->getContentSize().height);
    CCLOG("origin: (%f, %f)", origin.x, origin.y);
    m_pBackground->setPosition(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2);
    addChild(m_pBackground, LayerOrder::BACKGROUND);

    m_pPlayButton = cocos2d::ui::Button::create("play-btn.png");
    m_pPlayButton->setVisible(false);
    m_pPlayButton->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    m_pPlayButton->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    m_pPlayButton->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            auto scene = lorafel::TestScene::createScene();
            cocos2d::Director::getInstance()->replaceScene(scene);
        }
    });

    addChild(m_pPlayButton, LayerOrder::UX);

    m_pGoogleSignInButton = cocos2d::ui::Button::create("google-signin-btn.png");
    m_pGoogleSignInButton->setVisible(false);
    m_pGoogleSignInButton->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    m_pGoogleSignInButton->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    addChild(m_pGoogleSignInButton, LayerOrder::UX);

    m_pLoader = cocos2d::Sprite::createWithSpriteFrameName("avocado.png");
    m_pLoader->setVisible(false);
    m_pLoader->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    m_pLoader->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    addChild(m_pLoader, LayerOrder::UX);

    // Adds a selector association to be called from native end
    NDKHelper::addSelector("AuthStateMachineSelectors",
            "changeStateSelector",
            CC_CALLBACK_2(TitleScene::changeStateSelector, this),
            this);

    scheduleUpdate();

    return true;
}

void TitleScene::changeStateSelector(cocos2d::Node* sender, cocos2d::Value data) {
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();

        std::string state = valueMap["state"].asString();
        CCLOG("Response sent from native: %s", state.c_str());
    }

}

void TitleScene::update(float delta) {
    auto state = m_pStateMachine->getState();

    if(state->getName() == "LoggedOutState") {
        /**
         * If not logged in, then try logging in
         */
        m_pPlayButton->setVisible(false);
        m_pGoogleSignInButton->setVisible(false);
        m_pLoader->setVisible(true);
        m_pLoader->stopAllActions();

        if(FirebaseAuth::getInstance()->getAuth() != nullptr) {
            FirebaseAuth::getInstance()->initiateLoginProcess();
        }


    } else if(state->getName() == "NeverLoggedInState" || state->getName() == "AuthenticationFailedState") {
        /**
         * If user hasn't authorized a login, the
         * show the login buttons
         */
        m_pPlayButton->setVisible(false);
        m_pGoogleSignInButton->setVisible(true);
        m_pLoader->setVisible(false);
        m_pLoader->stopAllActions();
    } else if(state->getName() == "LoggedInState") {
        /**
         * If user is logged in and all is good,
         * then show the PLAY buttons and such
         */
        m_pPlayButton->setVisible(true);
        m_pGoogleSignInButton->setVisible(false);
        m_pLoader->setVisible(false);
        m_pLoader->stopAllActions();

    } else if(state->getName() == "AuthenticatingState") {
        /**
         * If currently trying to log in, then show
         * some sort of loader or something
         */
        m_pPlayButton->setVisible(false);
        m_pGoogleSignInButton->setVisible(false);
        m_pLoader->setVisible(true);
        auto spin = cocos2d::EaseInOut::create(cocos2d::RotateBy::create(1.0f, 1080), 1.0f);
        m_pLoader->runAction(cocos2d::RepeatForever::create(spin));
    }
    else {
        /**
         * huh?
         */
        m_pPlayButton->setVisible(false);
        m_pGoogleSignInButton->setVisible(true);
        m_pLoader->setVisible(false);
        m_pLoader->stopAllActions();
    }
}

TitleScene::~TitleScene() {
    NDKHelper::removeSelectorsInGroup("AuthStateMachineSelectors");
}

