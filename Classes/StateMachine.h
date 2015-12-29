//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_STATEMACHINE_H
#define LORAFEL_STATEMACHINE_H

#include <unordered_map>
#include "State.h"

namespace lorafel {

    class StateMachine {
    public:
        static StateMachine* create() {
                auto ref = new StateMachine();
                return ref;
        }

        template<class T>
        T * findState();

        template<typename T, class... Args>
        void addState(Args&&... args);

        template<typename T>
        bool canEnterState();

        template<typename T>
        bool enterState();

        template<typename T>
        bool setState();

        void updateWithDeltaTime(float delta);

        State * getState();

        ~StateMachine();

    private:
        std::unordered_map<std::string, State*> _states;
        State* _state;

        StateMachine();
    };

}

#endif //LORAFEL_STATEMACHINE_H
