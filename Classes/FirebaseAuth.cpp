//
// Created by Jarad DeLorenzo on 8/7/16.
//

#include "FirebaseAuth.h"

namespace lorafel {
    FirebaseAuth* FirebaseAuth::_instance;

    ::firebase::App* FirebaseAuth::getApp() const {
        #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
            firebase::App* app = firebase::App::Create(firebase::AppOptions(), my_jni_env, my_activity);
            return app;
        #else
            return firebase::App::Create(firebase::AppOptions());
        #endif
    }

    ::firebase::auth::Auth* FirebaseAuth::getAuth() const {
        return::firebase::auth::Auth::GetAuth(getApp());
    }

    bool FirebaseAuth::isAuthenticated() const {
        return getAuth()->CurrentUser() != nullptr;
    }

    void FirebaseAuth::initiateLoginProcess() {
        /**
         * TODO: Do some login stuff. For now,
         * just pretend we logged in
         */
        getAuth()->SignInWithCredentialLastResult();
        AuthStateMachine::getInstance()->setState<AuthenticatingState>();
    }
}