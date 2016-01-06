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
            _instance->addState<IdleState>();
            _instance->addState<BusyState>();
                _instance->addState<TileSwappingState>();
                _instance->addState<TileSwappingStartState>();
                _instance->addState<TileSwappingEndState>();
                _instance->addState<TileSwappingReverseStartState>();
                _instance->addState<TileSwappingReverseEndState>();
                _instance->addState<TileFallingState>();
                _instance->addState<MatchFoundState>();
                _instance->addState<TileQueueEmptiedState>();

            _instance->enterState<IdleState>();

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
