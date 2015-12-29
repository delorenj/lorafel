//
// Created by Jarad DeLorenzo on 12/28/15.
//

#ifndef LORAFEL_GAMESTATEMACHINE_H
#define LORAFEL_GAMESTATEMACHINE_H

#include "StateMachine.h"
#include "GameData.h"

namespace lorafel {

    class GameStateMachine : public StateMachine {
    public:
        GameStateMachine() : StateMachine(ST_MAX_STATES) {}

        // external events taken by this state machine
        void Dead();
        void Win(GameData*);
    private:
        // state machine state functions
        void ST_GameStarting();
        void ST_GameStarted();
        void ST_TilesFallingStart();
        void ST_TilesFallingEnd();
        void ST_MatchesFoundStart();
        void ST_MatchesFoundEnd();
        void ST_Idle();
        void ST_GameEnding();
        void ST_GameEnded();
        void ST_TilesSwapping();
        void ST_TilesSwapped();

        // state map to define state function order
        BEGIN_STATE_MAP
            STATE_MAP_ENTRY(ST_GameStarting)
            STATE_MAP_ENTRY(ST_GameStarted)
            STATE_MAP_ENTRY(ST_TilesFallingStart)
            STATE_MAP_ENTRY(ST_TilesFallingEnd)
            STATE_MAP_ENTRY(ST_MatchesFoundStart)
            STATE_MAP_ENTRY(ST_MatchesFoundEnd)
            STATE_MAP_ENTRY(ST_Idle)
            STATE_MAP_ENTRY(ST_GameEnding)
            STATE_MAP_ENTRY(ST_GameEnded)
            STATE_MAP_ENTRY(ST_TilesSwapping)
            STATE_MAP_ENTRY(ST_TilesSwapped)
        END_STATE_MAP

        // state enumeration order must match the order of state
        // method entries in the state map
        enum E_States {
            ST_GAME_STARTING = 0,
            ST_GAME_STARTED,
            ST_TILES_FALLING_START,
            ST_TILES_FALLING_END,
            ST_MATCHES_FOUND_START,
            ST_MATCHES_FOUND_END,
            ST_IDLE,
            ST_GAME_ENDING,
            ST_GAME_ENDED,
            ST_TILES_SWAPPING,
            ST_TILES_SWAPPED,
            ST_MAX_STATES
        };

    };

}

#endif //LORAFEL_GAMESTATEMACHINE_H
