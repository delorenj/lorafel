//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "SwappyGrid.h"
#include "GameStateMachine.h"
#include "Level.h"

using namespace lorafel;

bool SwappyGrid::init() {
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // Get a reference to the state machine
    m_pGameStateMachine = GameStateMachine::getInstance();
    m_pColumnStateMachines = new std::vector<StateMachine*>();
    m_pMoveStack = new std::stack<PlayerMove*>();
    m_pTileMatcher = new TileMatcher(this);
    m_pTileMatcher->setDebugDraw(false);

    for (int k = 0; k < NUM_COLUMNS; ++k) {
        auto fsm = StateMachine::create();
        fsm->addState<ColumnReadyToDropState>();
        fsm->addState<ColumnBusyState>();
        fsm->enterState<ColumnReadyToDropState>();
        m_pColumnStateMachines->push_back(fsm);
    }
    // Calculate the Tile size so we know how
    // big to make the grid
    auto spritecache = cocos2d::SpriteFrameCache::getInstance();
    auto originalTileSize = spritecache->getSpriteFrameByName("avocado.png")->getOriginalSizeInPixels();

    /**
     * m_tileScaleFactor = visibleSize.width/(NUM_COLUMNS * originalTileSize)
     */
    m_tileScaleFactor = (visibleSize.width-100)/(NUM_COLUMNS * originalTileSize.width);
    m_tileSize = originalTileSize * 1.15;
    setScale(m_tileScaleFactor);

    auto maxGridHeight = m_tileSize.height * NUM_ROWS;

    // Create Tile Grid
    m_pGrid = new TileGrid();
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        m_pGrid->push_back(new TileColumn(NUM_COLUMNS*2));
    }

    // Create Tile Drop Queues
    m_pTileDropQueues = new std::vector<TileQueue *>();

    // Create Tile Remove Queues
    // We need a queue so we only remove tiles in one
    // section of the update() loop
    m_pTileRemoveQueue = new TileQueue();

    int padding = 25;

    for (int j = 0; j < NUM_COLUMNS; ++j) {
        m_pTileDropQueues->push_back(new TileQueue());
    }
    setContentSize(cocos2d::Size(visibleSize.width+padding*4, visibleSize.width+padding*4));
    setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    setPosition(
            origin.x + visibleSize.width/2 + padding,
            visibleSize.height/2
    );

    this->scheduleUpdate();
    return true;
}

void SwappyGrid::update(float delta) {

    RemoveDeadTiles();

    ReplenishTiles();

    DropTiles();

    ProcessMatches();

//    FillInMissingTileGaps();
}

void SwappyGrid::DropTiles() {
    for (int k = 0; k < m_pTileDropQueues->size(); k++) {
        TileQueue * queue = m_pTileDropQueues->at(k);
        if(queue->empty()) continue;
        if(!columnReadyToDropTile(k)) continue;
        Tile* tile = queue->front();
        queue->pop();
        dropTile(k, tile);
    }
}

void SwappyGrid::RemoveDeadTiles() {
    GET_GAME_STATE
    if(state->getName() != "TileRemovedState") return;

    TileQueue* queue = m_pTileRemoveQueue;

    if(queue->empty() && getNumberOfFallingTiles() == 0) {
        GameStateMachine::getInstance()->enterState<IdleState>();
        return;
    }

    while(!queue->empty()) {
        Tile* tile = queue->front();
        queue->pop();
        if(tile->getReferenceCount() == 1) removeTile(tile);
    }

    for(auto x = 0; x < NUM_COLUMNS; x++) {
        for(auto y = 0; y < NUM_ROWS; y++) {
            auto tile = getTileAt(x, y);
            if(tile == nullptr) {
                // blank spot. let's fill in the blank
                Tile* nextTileAbove = getNextTileAbove(x, y);

                if(nextTileAbove == nullptr) continue; // nothing to slide down
                m_pGrid->at(x)->at(nextTileAbove->getGridPos().y) = nullptr;
                m_pGrid->at(x)->at(y) = nextTileAbove;
                nextTileAbove->moveToGridPos(x, y);
            }
        }
    }
}

Tile *SwappyGrid::getNextTileAbove(int x, int y) const {
    auto numberOfSlotsToSlideDown = 1;
    auto result = getTileAt(x, y+numberOfSlotsToSlideDown);
    while(result == nullptr && y+numberOfSlotsToSlideDown < NUM_ROWS) {
        numberOfSlotsToSlideDown++;
        result = getTileAt(x, y+numberOfSlotsToSlideDown);
    }
    return result;
}

void SwappyGrid::ReplenishTiles() {
    auto counts = getTileVacancyCounts();
    for (int i = 0; i < counts.size(); ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            addRandomTileToDropQueue(i);
        }
    }
}

void SwappyGrid::dropTile(int column, Tile *tile) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
    StateMachine* fsm = m_pColumnStateMachines->at(column);
    fsm->enterState<ColumnBusyState>();
    m_pGameStateMachine->enterState<TileFallingState>();
    m_numberOfFallingTiles++;
    int tileRowIndex = insertTileIntoColumn(column, tile);
    float dropTime = (float)(0.5);
    auto move = cocos2d::MoveTo::create(dropTime, gridToScreen(column, tileRowIndex));
    auto easeAction = cocos2d::EaseBounceOut::create(move->clone());

    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        Tile* tile = static_cast<Tile*>(sender);
        SwappyGrid* obj = static_cast<SwappyGrid*>(tile->getParent());
        obj->setNumberOfFallingTiles(obj->getNumberOfFallingTiles()-1);
        if(tileDropQueuesEmpty() && obj->getNumberOfFallingTiles() == 0) {
            m_pGameStateMachine->enterState<TileQueueEmptyMatchStartState>();
        }
    });

    auto sequence = cocos2d::Sequence::create(easeAction,callback, NULL);

    tile->runAction(sequence);
}

void SwappyGrid::insertTile(cocos2d::Vec2 pos, Tile *tile) {

}

void SwappyGrid::removeTile(cocos2d::Vec2 point) {

}

void SwappyGrid::swapTiles(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2) {

    if(m_pGameStateMachine->getState()->getName() == "IdleState" ||
            m_pGameStateMachine->getState()->getName() == "TileTouchMoveState") {
        m_pGameStateMachine->enterState<TileSwappingStartState>();
    } else {
        m_pGameStateMachine->enterState<TileSwappingReverseStartState>();
    }

    auto move1 = cocos2d::MoveTo::create(0.2, gridToScreen(pos2));
    auto move2 = cocos2d::MoveTo::create(0.2, gridToScreen(pos1));
    auto ease1 = cocos2d::EaseQuadraticActionOut::create(move1->clone());
    auto ease2 = cocos2d::EaseQuadraticActionOut::create(move2->clone());
    auto tile1 = m_pGrid->at(pos1.x)->at(pos1.y);
    auto tile2 = m_pGrid->at(pos2.x)->at(pos2.y);
    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        Tile* tempTile =  m_pGrid->at(pos1.x)->at(pos1.y);
        m_pGrid->at(pos1.x)->at(pos1.y) = m_pGrid->at(pos2.x)->at(pos2.y);
        m_pGrid->at(pos2.x)->at(pos2.y) = tempTile;

        if(m_pGameStateMachine->getState()->getName() == "TileSwappingStartState") {
            m_pGameStateMachine->enterState<TileSwappingEndState>();
        } else {
            m_pGameStateMachine->setState<IdleState>();
        }

    });

    auto sequence = cocos2d::Sequence::create(ease1,callback, NULL);
    move1->setTag(SWAPPING_ACTION_TAG);
    tile1->runAction(sequence);
    tile2->runAction(ease2);
}

void SwappyGrid::swapTiles(Tile *pTile, cocos2d::Vec2 vec2) {
    cocos2d::Vec2 gridPos1 = screenToGrid(pTile->getPosition());
    cocos2d::Vec2 gridPos2 = gridPos1 + vec2;
    swapTiles(gridPos1, gridPos2);
}


const cocos2d::Vec2 SwappyGrid::gridToScreen(cocos2d::Vec2 pos) const {
    return gridToScreen((int) pos.x, (int) pos.y);
}

const cocos2d::Vec2 SwappyGrid::gridToScreen(int x, int y) const {
    return cocos2d::Vec2(
            m_tileSize.width*x,
            m_tileSize.height*y
    );
}

const cocos2d::Vec2 SwappyGrid::screenToGrid(cocos2d::Vec2 pos) const {
    return cocos2d::Vec2(
            (int)pos.x/(int)m_tileSize.width,
            (int)pos.y/(int)m_tileSize.height
    );
}

const cocos2d::Vec2 SwappyGrid::getTopOfScreen() const {
    return convertToNodeSpace(cocos2d::Vec2(0, visibleSize.height));
}

const int SwappyGrid::getTopOffscreenTileSlot() const {
    return (int)(getTopOfScreen().y/m_tileSize.height);
}

int SwappyGrid::insertTileIntoColumn(int columnNumber, Tile *tile, bool fromTop) {
    TileColumn* col = m_pGrid->at(columnNumber);
    auto lowest = lowestVacancyInColumn(columnNumber);
    col->at(lowest) = tile;
    return lowest;
}

bool SwappyGrid::overflow() {
    for(auto col : *m_pGrid) {
        if(col->size() > NUM_ROWS) return true;
    }

    return false;
}

/**
 * Returns the number of free spots available to
 * drop tiles in each column. This is number of
 * tiles in the grid, and tiles waiting to be
 * dropped in the TileDropQueue.
 */
std::vector<int> SwappyGrid::getTileVacancyCounts() {
    auto counts = std::vector<int>();
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        int count = 0;
        for (int j = 0; j < NUM_ROWS; ++j) {
            if(getTileAt(i,j)) {
                count++;
            }
        }

        int numTilesInGridCol = count;
        int numTilesWaitingToDropInCol = m_pTileDropQueues->at(i)->size();
        counts.push_back(NUM_ROWS - numTilesWaitingToDropInCol - numTilesInGridCol);
    }

    return counts;
}

void SwappyGrid::addTileToDropQueue(int column, Tile *pTile) {
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS && column < m_pTileDropQueues->size());
    pTile->setGrid(this);

    // Put tile in the correct place
    // but don't drop it yet.
    cocos2d::Vec2 newPos = gridToScreen(column, getTopOffscreenTileSlot());
    pTile->setPosition(newPos);
    addChild(pTile,2);

    // Drop the random tile in the given column
    // using the drop queue to ensure it only
    // drops when allowed
    TileQueue * q = m_pTileDropQueues->at(column);
    q->push(pTile);

}

void SwappyGrid::addRandomTileToDropQueue(int column) {
    Tile* tile = getLevel()->getRandomTile();
    addTileToDropQueue(column, tile);
}

bool SwappyGrid::columnReadyToDropTile(int column) {
    /**
     * Loop through all sprites in that column
     * If any are in the top slot, then hold off
     * on dropping any more
     */
    auto fsm = (StateMachine *) m_pColumnStateMachines->at(column);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            auto tile = getTileAt(i, j);
            if(!tile) continue;
            auto bb = tile->getBoundingBox();
            if(bb.containsPoint(gridToScreen(column, getTopOffscreenTileSlot()-1))) {
                fsm->enterState<BusyState>();
                return false;
            }
        }

    }
    fsm->enterState<ColumnReadyToDropState>();
    return true;
}

void SwappyGrid::setCurrentTouchId(unsigned int eventTouchId) {
    this->m_currentTouchId = eventTouchId;
}

unsigned int SwappyGrid::getCurrentTouchId() {
    return this->m_currentTouchId;
}

void SwappyGrid::ProcessMatches() {
    GET_GAME_STATE
    // Checking for matches can happen at a couple of places
    // 1. After all the tiles that are going to fall, are done falling
    // 2. After a user's valid move
    // TODO: Refactor state to have a member function canCheckForMatches(). This may be cleaner
    if(state->getName() != "TileQueueEmptyMatchStartState" &&
            state->getName() != "TileSwappingEndState") {
        return;
    }

    auto matches = m_pTileMatcher->findMatches();

    if(matches.size() > 0) {
        if(!m_pMoveStack->empty()) {
            m_pMoveStack->top()->setMatched(true);
        }
        m_pGameStateMachine->enterState<MatchFoundState>();
        for(auto match : matches) {
            match->run();
        }
        GameStateMachine::getInstance()->enterState<IdleState>();
    } else if(!m_pMoveStack->empty() && !m_pMoveStack->top()->isMatched()) {
        // Only revert tiles when no match is found AND the match was
        // initiated by player move. If match initiated by falling tiles
        // then that means the player move was valid and no need to revert
        auto playerMove = m_pMoveStack->top();
        m_pMoveStack->pop();
        playerMove->cancel();

    } else {
        GameStateMachine::getInstance()->enterState<IdleState>();
    }
}

bool SwappyGrid::isTilePresentAt(cocos2d::Vec2 pos) {
    Tile* tile = getTileAt(pos);
    return tile == nullptr ? false : true;

}

bool SwappyGrid::tileDropQueuesEmpty() {
    bool count = 0;
    for(auto q : *m_pTileDropQueues) {
        count += q->size();
    }
    return count == 0;
}

unsigned int SwappyGrid::getNumberOfFallingTiles() const {
    return m_numberOfFallingTiles;
}

TileSwapEventData *SwappyGrid::getTileSwapEventData() const { return m_pTileSwapEventData; }

void SwappyGrid::setNumberOfFallingTiles(unsigned int m_numberOfFallingTiles) {
    SwappyGrid::m_numberOfFallingTiles = m_numberOfFallingTiles;
}

Tile* SwappyGrid::getTileAt(const cocos2d::Vec2 pos) const {
    if(pos.x >= m_pGrid->size()) {
        return nullptr;
    }

    TileColumn* col = m_pGrid->at(pos.x);
    if(pos.y >= col->size()) {
        return nullptr;
    } else {
        return col->at(pos.y);
    }
}

Tile* SwappyGrid::getTileAt(const int x, const int y) const {
    return getTileAt(cocos2d::Vec2(x,y));
}

void SwappyGrid::clearVisitStates() {
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            auto tile = getTileAt(i,j);
            if(!tile) continue;
            tile->setVisitColor(Tile::NONE);
            tile->setVisitOrder(0);
            tile->removeAllChildrenWithCleanup(true);
        }
    }
}

void SwappyGrid::setLevel(Level *pLevel) {
    m_pLevel = pLevel;
}

Level *SwappyGrid::getLevel() {
    return m_pLevel;
}

void SwappyGrid::FillInMissingTileGaps() {
    GET_GAME_STATE
    if(state->getName() != "TileRemovedState") return;

    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 1; j < NUM_ROWS; ++j) {    // no need to check the lowest row
            auto tile = getTileAt(i, j);
            // if tile exists and has empty space below it
            // the fill in the gap
            if(tile && !tile->getBottom()) {
                int lowest = lowestVacancyInColumn(i);
                m_pGrid->at(i)->at(lowest) = tile;
                m_pGrid->at(i)->at(j) = nullptr;
                setNumberOfFallingTiles(getNumberOfFallingTiles() + 1);
                tile->moveToGridPos(i, lowest);
            }
        }
    }
    if(getNumberOfFallingTiles() == 0) {
        GameStateMachine::getInstance()->enterState<IdleState>();
    }
}

int SwappyGrid::lowestVacancyInColumn(int i) {
    Tile* tile;
    int j = 0;
    do {
        tile = getTileAt(i,j++);
    } while(tile != nullptr);

    return j-1;
}

void SwappyGrid::removeTile(Tile *tile) {
    if(tile == nullptr) return;
    auto pos = tile->getGridPos();
    m_pGrid->at(pos.x)->at(pos.y) = nullptr;
    removeChild(tile);
}

void SwappyGrid::addTileToRemoveQueue(Tile *pTile) {
    m_pTileRemoveQueue->push(pTile);
}
