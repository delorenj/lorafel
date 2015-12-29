//
// Created by Jarad DeLorenzo on 12/28/15.
//

#include "GameStateMachine.h"

using namespace lorafel;

void GameStateMachine::ST_Idle() {
    // given the Idle event, transition to a new state based upon
    // the current state of the state machine
    BEGIN_TRANSITION_MAP                      // - Current State -
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_GameStarting
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_GameStarted
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)        // ST_TilesFallingStart
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)  // ST_TilesFallingEnd
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)        // ST_MatchesFoundStart
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)  // ST_MatchesFoundEnd
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_Idle
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)        // ST_GameEnding
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_GameEnded
            TRANSITION_MAP_ENTRY (EVENT_IGNORED)        // ST_TilesSwapping
            TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)        // ST_TileSwapped

    END_TRANSITION_MAP(NULL)
}

void GameStateMachine::ST_GameStarting() {

}

void GameStateMachine::ST_GameStarted() {

}

void GameStateMachine::ST_TilesFallingStart() {

}

void GameStateMachine::ST_TilesFallingEnd() {

}

void GameStateMachine::ST_MatchesFoundStart() {

}

void GameStateMachine::ST_MatchesFoundEnd() {

}

void GameStateMachine::ST_GameEnding() {

}

void GameStateMachine::ST_GameEnded() {

}

void GameStateMachine::ST_TilesSwapping() {

}

void GameStateMachine::ST_TilesSwapped() {

}

void GameStateMachine::Dead() {

}

void GameStateMachine::Win(GameData *data) {

}
