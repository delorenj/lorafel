//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_GAMESTATES_H
#define LORAFEL_GAMESTATES_H

#include "State.h"

namespace lorafel {

    class ColumnState : public State {
    public:
        ColumnState()  {};
        ~ColumnState() {};
        virtual bool canDropTile() = 0;
        bool isValidNextState(State* state) override { return true; }
        const std::string getName() const override { return "ColumnState"; }
    };

    class ColumnReadyToDropState : public ColumnState {
        virtual bool canDropTile() override { return true; }
        const std::string getName() const override { return "ColumnReadyToDropState"; }
    };

    class ColumnBusyState : public ColumnState {
        virtual bool canDropTile() override { return false; }
        const std::string getName() const override { return "ColumnBusyState"; }
    };

    class GameState : public State {
    public:
        GameState()  {};
        ~GameState() {};
        const std::string getName() const override { return "GameState"; }
        bool isValidNextState(State* state) override { return true; }
        virtual bool isBusy() const = 0;

//        virtual void didEnterWithPreviousState(State *previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State *nextState);
    };

    // Waiting for player's move
    class IdleState : public GameState
    {
    public:
        IdleState() { };
        const std::string getName() const override { return "IdleState"; }
        bool isBusy() const override { return false; }

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

    class BusyState : public GameState
    {
    public:
        BusyState() {};
        const std::string getName() const override { return "BusyState"; }
        bool isBusy() const override { return true; }
//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

    class TileSwappingState : public BusyState
    {
    public:
        TileSwappingState() {} ;
        const std::string getName() const override { return "TileSwappingState"; }

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state)
    };

    class MatchFoundState : public BusyState
    {
    public:
        MatchFoundState() {};
        const std::string getName() const override { return "MatchFoundState"; }

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

    class TileFallingState : public BusyState
    {
    public:
        TileFallingState() {} ;
        const std::string getName() const override { return "TileFallingState"; }

//        virtual void didEnterWithPreviousState(State* previousState);
//        virtual void updateWithDeltaTime(float delta);
//        virtual void willExitWithNextState(State* nextState);
//        virtual bool isValidNextState(State* state);
    };

}

#endif //LORAFEL_GAMESTATES_H
