//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_GAMESTATES_H
#define LORAFEL_GAMESTATES_H

#include "State.h"

namespace lorafel {

    // Column States
    //
    //
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

    // GameStates
    //
    //
    class GameState : public State {
    public:
        GameState()  {};
        ~GameState() {};
        const std::string getName() const override { return "GameState"; }
        virtual bool isValidNextState(State* state) override { return true; }
        virtual bool isBusy() const = 0;
        virtual bool canCheckForMatches() const = 0;
    };

    // Waiting for player's move
    class IdleState : public GameState {
    public:
        IdleState() { };
        const std::string getName() const override { return "IdleState"; }
        bool isBusy() const override { return false; }
        virtual bool canCheckForMatches() const override { return false; }
        virtual bool isValidNextState(State* state) override {
            if(state->getName() == "TileFallingState") { return true; }
            if(state->getName() == "TileSwappingStartState") { return true; }
        }
    };

    class BusyState : public GameState {
    public:
        BusyState() {};
        const std::string getName() const override { return "BusyState"; }
        bool isBusy() const override { return true; }
        virtual bool canCheckForMatches() const override { return false; }
    };


    class TileSwappingState : public BusyState {
    public:
        TileSwappingState() {} ;
        virtual ~TileSwappingState() {} ;
        virtual const std::string getName() const override { return "TileSwappingState"; }
    };

    class TileSwappingStartState : public TileSwappingState {
    public:
        TileSwappingStartState() {} ;
        const std::string getName() const override { return "TileSwappingStartState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileSwappingEndState") { return true; }
            return false;
        }
    };

    class TileSwappingEndState : public TileSwappingState{
    public:
        TileSwappingEndState() {} ;
        const std::string getName() const override { return "TileSwappingEndState"; }
        virtual bool canCheckForMatches() const override { return true; }
    };

    class TileSwappingReverseEndState;
    class TileSwappingReverseStartState : public TileSwappingState {
    public:
        TileSwappingReverseStartState() {} ;
        const std::string getName() const override { return "TileSwappingReverseStartState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileSwappingReverseEndState") { return true; }
            return false;
        }
    };

    class TileSwappingReverseEndState : public TileSwappingState {
    public:
        TileSwappingReverseEndState() {} ;
        const std::string getName() const override { return "TileSwappingReverseEndState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "IdleState") { return true; }
            return false;
        }
    };

    class MatchFoundState : public BusyState {
    public:
        MatchFoundState() {};
        const std::string getName() const override { return "MatchFoundState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileRemovedState") { return true; }
            return false;
        }
    };

    class TileRemovedState : public BusyState {
    public:
        TileRemovedState() {};
        const std::string getName() const override { return "TileRemovedState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileFallingState") { return true; }
            return false;
        }
    };

    class TileFallingState : public BusyState {
    public:
        TileFallingState() {} ;
        const std::string getName() const override { return "TileFallingState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileQueueEmptyMatchStartState") { return true; }
            return false;
        }
    };

    class TileQueueEmptyMatchStartState : public BusyState {
    public:
        TileQueueEmptyMatchStartState() {};
        const std::string getName() const override { return "TileQueueEmptyMatchStartState"; }
        bool canCheckForMatches() const override { return true; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "IdleState") { return true; }
            if(state->getName() == "MatchFoundState") { return true; }
            return false;
        }
    };


}

#endif //LORAFEL_GAMESTATES_H
