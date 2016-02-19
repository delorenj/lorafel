//
// Created by Jarad DeLorenzo on 2/12/16.
//

#include "DragDropSwapPlayerMove.h"
#include "GameStateMachine.h"

using namespace lorafel;

void DragDropSwapPlayerMove::run() {
    m_pSwappyGrid->swapTiles(m_originGridPos, m_destGridPos);
}

bool DragDropSwapPlayerMove::isValid() {
    return m_pSwappyGrid->getTileAt(m_destGridPos)->getVisitColor() == Tile::Color::YELLOW;
}

void DragDropSwapPlayerMove::cancel() {
    m_pSwappyGrid->swapTiles(m_destGridPos, m_originGridPos);
}
