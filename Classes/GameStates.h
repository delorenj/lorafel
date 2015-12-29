//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_GAMESTATES_H
#define LORAFEL_GAMESTATES_H

#include "State.h"

namespace lorafel {

    class GameState : public State {
    public:
        GameState()  {};
        ~GameState() {};

//        virtual void didEnterWithPreviousState(State *previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State *nextState);
//        virtual bool isValidNextState(State *state);
    };

    // Waiting for player's move
    class IdleState : public GameState
    {
    public:
        IdleState() { };

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

    class BusyState : public GameState
    {
    public:
//        BusyState();

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

    class TileSwappingState : public BusyState
    {
    public:
//        TileSwappingState();

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

    class MatchFoundState : public BusyState
    {
    public:
//        MatchFoundState();

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

    class TileFallingState : public BusyState
    {
    public:
//        TileFallingState()

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

}

#endif //LORAFEL_GAMESTATES_H
