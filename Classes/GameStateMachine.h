//
// Created by Jarad DeLorenzo on 12/29/15.
//

#ifndef LORAFEL_GAMESTATEMACHINE_H
#define LORAFEL_GAMESTATEMACHINE_H

#include "StateMachine.h"
#include "GameStates.h"

namespace lorafel {

    class GameStateMachine : public StateMachine {
    protected:
        static StateMachine* _instance;

        static void initStates() {
            _instance->addState<GameState>();
                _instance->addState<IdleState>();
                _instance->addState<BusyState>();
                    _instance->addState<TileSwappingState>();
                    _instance->addState<TileFallingState>();
                    _instance->addState<MatchFoundState>();

            _instance->enterState<BusyState>();

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

#endif //LORAFEL_GAMESTATEMACHINE_H
