//
// Created by Jarad DeLorenzo on 8/7/16.
//

#include "firebase/app.h"
#include "firebase/auth.h"
#include "FirebaseAuth.h"

//#define CC_TARGET_PLATFORM CC_PLATFORM_ANDROID

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"
#include "google_play_services/availability.h"
#endif

namespace lorafel {
    FirebaseAuth* FirebaseAuth::_instance;

    firebase::App* FirebaseAuth::getApp() {
        if(m_pApp == nullptr) {
            #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                CCLOG("About to create the Firebase app");
                m_pApp = ::firebase::App::Create(firebase::AppOptions(), cocos2d::JniHelper::getEnv(), cocos2d::JniHelper::GetActivity());
                CCLOG("Done Creating the Firebase appppp");
                CCLOG("Ancho-Salmon dong-deli");
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
        auto app = getApp();

        bool try_again;
        ::firebase::InitResult init_result;
        ::firebase::auth::Auth* auth;

        do {
            try_again = false;
            auth = ::firebase::auth::Auth::GetAuth(app, &init_result);

            #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                // On Android, we need to update or activate Google Play services
                // before we can initialize this Firebase module.
                if (init_result == firebase::kInitResultFailedMissingDependency) {
                  CCLOG("Google Play services unavailable, trying to fix.");
                  firebase::Future<void> make_available =
                      google_play_services::MakeAvailable(app->GetJNIEnv(),
                                                          app->activity());
                  while (make_available.Status() != ::firebase::kFutureStatusComplete) {
                    CCLOG("waiting...");
                  }

                  if (make_available.Error() == 0) {
                    CCLOG("Google Play services now available, continuing.");
                    try_again = true;
                  } else {
                    CCLOG("Google Play services still unavailable.");
                  }
                }
            #endif
        } while (try_again);

        if (init_result != firebase::kInitResultSuccess) {
            CCLOG("Failed to initialize Auth, exiting.");
            return nullptr;
        } else {
            return auth;
        }
    }

    bool FirebaseAuth::isAuthenticated() {
        return getAuth()->CurrentUser() != nullptr;
    }

    void FirebaseAuth::initiateLoginProcess() {
        m_future = getAuth()->SignInWithCredentialLastResult();
        AuthStateMachine::getInstance()->setState<AuthenticatingState>();
    }
}