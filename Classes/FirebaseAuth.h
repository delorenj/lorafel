//
// Created by Jarad DeLorenzo on 8/7/16.
//

#ifndef LORAFEL_FIREBASEAUTH_H
#define LORAFEL_FIREBASEAUTH_H

#include "firebase/app.h"
#include "firebase/auth.h"
#include "AuthStateMachine.h"

namespace lorafel {
    class FirebaseAuth {
    public:
        static FirebaseAuth *getInstance() {
            if (_instance == nullptr) {
                _instance = new FirebaseAuth();
            }
            return _instance;
        }

        ::firebase::App* getApp();
        ::firebase::auth::Auth* getAuth();
        bool isAuthenticated();

        void initiateLoginProcess();

    protected:
        static FirebaseAuth *_instance;

        firebase::App* m_pApp;
    };
}

#endif //LORAFEL_FIREBASEAUTH_H
