//
// Created by Jarad DeLorenzo on 2/12/16.
//

#include "DragDropSwapPlayerMove.h"
#include "GameStateMachine.h"

void lorafel::DragDropSwapPlayerMove::run() {
    auto gsm = GameStateMachine::getInstance();
    auto state = gsm->getState();

    if (state->getName() == "IdleState" || state->getName() == "TileTouchMoveState") {
        gsm->enterState<TileSwappingStartState>();
    }

    auto move1 = cocos2d::MoveTo::create(0.2, m_pSwappyGrid->gridToScreen(m_pTile2->getGridPos()));
    auto move2 = cocos2d::MoveTo::create(0.2, m_origin);
    auto ease1 = cocos2d::EaseQuadraticActionOut::create(move1->clone());
    auto ease2 = cocos2d::EaseQuadraticActionOut::create(move2->clone());
    auto tile1 = m_pTile1;
    auto tile2 = m_pTile2;
    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        auto callBackState = gsm->getState();
        auto pos1 = m_pTile1->getGridPos();
        auto pos2 = m_pTile2->getGridPos();
        auto grid = m_pSwappyGrid->getGrid();

        Tile* tempTile = grid->at(pos1.x)->at(pos1.y);
        grid->at(pos1.x)->at(pos1.y) = grid->at(pos2.x)->at(pos2.y);
        grid->at(pos2.x)->at(pos2.y) = tempTile;

        if (callBackState->getName() == "TileSwappingStartState") {
            gsm->enterState<TileSwappingEndState>();
        } else {
            gsm->setState<IdleState>();
        }
    });

    auto sequence = cocos2d::Sequence::create(ease1, callback, NULL);
    move1->setTag(SwappyGrid::SWAPPING_ACTION_TAG);
    tile1->runAction(sequence);
    tile2->runAction(ease2);
}

bool lorafel::DragDropSwapPlayerMove::isValid() {
    return m_pTile2->getVisitColor() == Tile::Color::YELLOW;
}

void lorafel::DragDropSwapPlayerMove::cancel() {

}
