//
// Created by Jarad DeLorenzo on 2/12/16.
//

#include "DragDropSwapPlayerMove.h"
#include "GameStateMachine.h"

void lorafel::DragDropSwapPlayerMove::run() {
    auto gsm = GameStateMachine::getInstance();
    auto state = gsm->getState();

    if (state->getName() == "IdleState" ||
            state->getName() == "TileTouchMoveState") {
        gsm->enterState<TileSwappingStartState>();
    } else {
        gsm->enterState<TileSwappingReverseStartState>();
    }

    auto move1 = cocos2d::MoveTo::create(0.2, m_pSwappyGrid->gridToScreen(m_pTile2->getGridPos()));
    auto move2 = cocos2d::MoveTo::create(0.2, m_pSwappyGrid->gridToScreen(m_pTile1->getGridPos()));
    auto ease1 = cocos2d::EaseQuadraticActionOut::create(move1->clone());
    auto ease2 = cocos2d::EaseQuadraticActionOut::create(move2->clone());
    auto tile1 = m_pTile1;
    auto tile2 = m_pTile2;
    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        Tile* tempTile = m_pSwappyGrid->getGrid()->at(m_pTile1->getGridPos().x)->at(m_pTile1->getGridPos().y);
        m_pSwappyGrid->getGrid()->at(m_pTile1->getGridPos().x)->at(m_pTile1->getGridPos().y) = m_pSwappyGrid->getGrid()->at(m_pTile2->getGridPos().x)->at(m_pTile2->getGridPos().y);
        m_pSwappyGrid->getGrid()->at(m_pTile2->getGridPos().x)->at(m_pTile2->getGridPos().y) = tempTile;

        if (state->getName() == "TileSwappingStartState") {
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
    return true;
}

void lorafel::DragDropSwapPlayerMove::cancel() {

}
