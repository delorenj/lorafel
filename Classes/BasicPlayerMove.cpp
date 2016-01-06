//
// Created by Jarad DeLorenzo on 1/4/16.
//

#include "BasicPlayerMove.h"

void lorafel::BasicPlayerMove::run() {
    CCLOG("Running Basic Move");
    m_pSwappyGrid->swapTiles(m_pos1, m_pos2);

}

void lorafel::BasicPlayerMove::cancel() {
    CCLOG("Canceling Basic Move");
    m_pSwappyGrid->swapTiles(m_pos2, m_pos1);
}

bool lorafel::BasicPlayerMove::isValid() {
    if(!m_pSwappyGrid->isTilePresentAt(m_pos1) || !m_pSwappyGrid->isTilePresentAt(m_pos2)) {
        return false;
    } else if(!m_pSwappyGrid->getTileAt(m_pos1)->isSwappable() || !m_pSwappyGrid->getTileAt(m_pos2)->isSwappable()) {
        return false;
    } else {
        return true;
    }

}
