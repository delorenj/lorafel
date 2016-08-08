//
// Created by Jarad DeLorenzo on 8/7/16.
//

#ifndef LORAFEL_AUTHSTATEMACHINE_H
#define LORAFEL_AUTHSTATEMACHINE_H

#include "StateMachine.h"
#include "GameStates.h"

namespace lorafel {
    class AuthStateMachine : public StateMachine {
    protected:
        static StateMachine* _instance;

        static void initStates() {
            _instance->addState<NeverLoggedInState>();
            _instance->addState<LoggedInState>();
            _instance->addState<LoggedOutState>();
            _instance->addState<AuthenticatingState>();
            _instance->addState<AuthenticationFailedState>();
        }

    public:
        static StateMachine* getInstance() {
            if(_instance == nullptr) {
                _instance = StateMachine::create();
                initStates();
            }
            return _instance;
        }
    };
}

#endif //LORAFEL_AUTHSTATEMACHINE_H
