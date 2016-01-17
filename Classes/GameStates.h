//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_GAMESTATES_H
#define LORAFEL_GAMESTATES_H

#include "cocos2d.h"
#include "State.h"

namespace lorafel {

    // Column States
    //
    //
    class ColumnState : public State {
    public:
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
        virtual const std::string getName() const override { return "GameState"; }
        virtual bool isValidNextState(State* state) override { return true; }
        virtual bool isBusy() const = 0;
    };

    // Waiting for player's move
    class IdleState : public GameState {
    public:
        virtual const std::string getName() const override { return "IdleState"; }
        virtual bool isBusy() const override { return false; }
        virtual bool isValidNextState(State* state) override {
            if(state->getName() == "TileFallingState")      return true;
            if(state->getName() == "TileTouchStartState")   return true;
        }
    };

    class BusyState : public GameState {
    public:
        const std::string getName() const override { return "BusyState"; }
        virtual bool isBusy() const override { return true; }
    };

    class TileTouchState : public BusyState {
    public:
        virtual const std::string getName() const override { return "TileTouchState"; }
        cocos2d::Vec2 getTouchStartPos() const { return m_touchStartPos; }
        void setTouchStartPos(const cocos2d::Vec2 &pos) { m_touchStartPos = pos; }
        cocos2d::Vec2 getTileStartPos() const { return m_tileStartPos; }
        void setTileStartPos(const cocos2d::Vec2 &pos) { m_tileStartPos = pos; }

        bool isValidNextState(State* state) override {
            if(state->getName() == "TileSwappingStartState") return true;
            if(state->getName() == "TileTouchEndState") return true;
        }

    protected:
        cocos2d::Vec2 m_touchStartPos;
        cocos2d::Vec2 m_tileStartPos;

    };

    class TileTouchStartState : public TileTouchState {
    public:
        virtual const std::string getName() const override { return "TileTouchStartState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileSwappingStartState") return true;
            if(state->getName() == "TileTouchMoveState") return true;
            if(state->getName() == "TileTouchEndState") return true;
            if(state->getName() == "IdleState") return true;
        }
    };

    class TileTouchEndState : public TileTouchState {
    public:
        virtual const std::string getName() const override { return "TileTouchEndState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "IdleState") return true;
        }

    };

    class TileTouchMoveState : public TileTouchState {
    public:
        virtual const std::string getName() const override { return "TileTouchMoveState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "IdleState") return true;
            if(state->getName() == "TileSwappingStartState") return true;
        }
    };

    class TileSwappingState : public TileTouchMoveState {
    public:
        virtual const std::string getName() const override { return "TileSwappingState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileTouchEndState") return true;
        }

    };

    class TileSwappingStartState : public TileSwappingState {
    public:
        virtual const std::string getName() const override { return "TileSwappingStartState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileSwappingEndState") return true;
            return false;
        }
    };

    class TileSwappingEndState : public TileSwappingState{
    public:
        virtual const std::string getName() const override { return "TileSwappingEndState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileSwappingReverseStartState") return true;
            if(state->getName() == "MatchFoundState") return true;
            return false;
        }

    };

    class TileSwappingReverseEndState;
    class TileSwappingReverseStartState : public TileTouchEndState {
    public:
        virtual const std::string getName() const override { return "TileSwappingReverseStartState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileSwappingReverseEndState") return true;
            return false;
        }
    };

    class TileSwappingReverseEndState : public TileTouchEndState {
    public:
        virtual const std::string getName() const override { return "TileSwappingReverseEndState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "IdleState") return true;
            return false;
        }
    };

    class MatchFoundState : public BusyState {
    public:
        const std::string getName() const override { return "MatchFoundState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileRemovedState") return true;
            return false;
        }
    };

    class TileRemovedState : public BusyState {
    public:
        const std::string getName() const override { return "TileRemovedState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileFallingState") return true;
            return false;
        }
    };

    class TileFallingState : public BusyState {
    public:
        const std::string getName() const override { return "TileFallingState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "TileQueueEmptyMatchStartState") return true;
            return false;
        }
    };

    class TileQueueEmptyMatchStartState : public BusyState {
    public:
        const std::string getName() const override { return "TileQueueEmptyMatchStartState"; }
        bool isValidNextState(State* state) override {
            if(state->getName() == "IdleState") return true;
            if(state->getName() == "MatchFoundState") return true;
            return false;
        }
    };

}

#endif //LORAFEL_GAMESTATES_H
