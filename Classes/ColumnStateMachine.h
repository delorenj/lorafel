//
// Created by Jarad DeLorenzo on 1/1/16.
//

#ifndef LORAFEL_COLUMNSTATEMACHINE_H
#define LORAFEL_COLUMNSTATEMACHINE_H

#include "StateMachine.h"
#include "GameStates.h"

namespace lorafel {

    class ColumnStateMachine : public StateMachine {
        protected:
            static StateMachine* _instance;

            static void initStates() {
                _instance->addState<ColumnReadyToDropState>();
                _instance->addState<ColumnBusyState>();

                _instance->enterState<ColumnReadyToDropState>();

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

    };

}
#endif //LORAFEL_COLUMNSTATEMACHINE_H
