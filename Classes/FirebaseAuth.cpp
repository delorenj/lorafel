//
// Created by Jarad DeLorenzo on 8/7/16.
//

#include "FirebaseAuth.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"
#endif

namespace lorafel {
    FirebaseAuth* FirebaseAuth::_instance;

    ::firebase::App* FirebaseAuth::getApp() {
        if(m_pApp == nullptr) {
            #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                m_pApp = firebase::App::Create(firebase::AppOptions(), cocos2d::JniHelper::getEnv(), cocos2d::JniHelper::GetActivity());
            #else
                m_pApp = firebase::App::Create(firebase::AppOptions());
            #endif
        }

        if(m_pApp == nullptr) {
            m_pApp = firebase::App::GetInstance();
        }
        return m_pApp;
    }

    ::firebase::auth::Auth* FirebaseAuth::getAuth() {
        return::firebase::auth::Auth::GetAuth(getApp());
    }

    bool FirebaseAuth::isAuthenticated() {
        return getAuth()->CurrentUser() != nullptr;
    }

    void FirebaseAuth::initiateLoginProcess() {
        m_future = getAuth()->SignInWithCredentialLastResult();
        AuthStateMachine::getInstance()->setState<AuthenticatingState>();
    }
}