//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "SwappyGrid.h"
#include "GameStateMachine.h"

using namespace lorafel;

bool SwappyGrid::init() {
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // Get a reference to the state machine
    m_pGameStateMachine = GameStateMachine::getInstance();
    m_pColumnStateMachines = new std::vector<StateMachine*>();
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
    m_tileSize = spritecache->getSpriteFrameByName("avocado.png")->getOriginalSizeInPixels();
    m_tileSize.width += 5;
    m_tileSize.height += 5;
    auto maxGridHeight = m_tileSize.height * NUM_ROWS;

    auto tileWidth = m_tileSize.width;
    m_tileScaleFactor = m_tileSize.width/tileWidth;

    // Physics Bounds
    auto body = cocos2d::PhysicsBody::createEdgeSegment(
            cocos2d::Vec2(0, 0),
            cocos2d::Vec2(tileWidth*NUM_COLUMNS,0),
            cocos2d::PHYSICSBODY_MATERIAL_DEFAULT,
            3
    );

    auto edgeNode = cocos2d::Node::create();
    edgeNode->setPhysicsBody(body);
    addChild(edgeNode);

    // Create Tile Grid
    m_pGrid = new TileGrid();
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        m_pGrid->push_back(new TileColumn());
    }

    // Create Tile Drop Queues
    m_pTileDropQueues = new std::vector<TileDropQueue*>();
    for (int j = 0; j < NUM_COLUMNS; ++j) {
        m_pTileDropQueues->push_back(new TileDropQueue());
    }

    this->setPosition(
            origin.x + visibleSize.width/2 - m_tileSize.width*NUM_COLUMNS/2,
            visibleSize.height - maxGridHeight - m_tileSize.height*3
    );

    this->scheduleUpdate();
    return true;
}

void SwappyGrid::loadLevel(Level *level) {
    //Set the grid's level
    this->level = level;
}

void SwappyGrid::update(float delta) {

    auto counts = getTileVacancyCounts();
    for (int i = 0; i < counts.size(); ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            addRandomTileToDropQueue(i);
        }
    }

    for (int k = 0; k < m_pTileDropQueues->size(); k++) {
        TileDropQueue* queue = m_pTileDropQueues->at(k);
        if(queue->empty()) continue;
        if(!columnReadyToDropTile(k)) continue;
        Tile* tile = queue->front();
        queue->pop();
        dropTile(k, tile);
    }
}

void SwappyGrid::dropTile(int column, Tile *tile) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
    StateMachine* fsm = m_pColumnStateMachines->at(column);
    fsm->enterState<ColumnBusyState>();
    int tileRowIndex = insertTileIntoColumn(column, tile);
    float dropTime = (float)(0.75);
    auto move = cocos2d::MoveTo::create(dropTime, gridToScreen(column, tileRowIndex));
    auto easeAction = cocos2d::EaseBounceOut::create(move->clone());
    tile->runAction(easeAction);
}

void SwappyGrid::insertTile(cocos2d::Vec2 pos, Tile *tile) {

}

void SwappyGrid::removeTile(cocos2d::Vec2 point) {

}

void SwappyGrid::swapTiles(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2) {
    CCLOG("Swapping (%f, %f) <--> (%f, %f)", pos1.x, pos1.y, pos2.x, pos2.y);
    m_pGameStateMachine->enterState<TileSwappingState>();
    auto move1 = cocos2d::MoveTo::create(0.2, gridToScreen(pos2));
    auto move2 = cocos2d::MoveTo::create(0.2, gridToScreen(pos1));
    auto ease1 = cocos2d::EaseQuadraticActionOut::create(move1->clone());
    auto ease2 = cocos2d::EaseQuadraticActionOut::create(move2->clone());
    auto tile1 = m_pGrid->at(pos1.x)->at(pos1.y);
    auto tile2 = m_pGrid->at(pos2.x)->at(pos2.y);

    auto callback = cocos2d::CallFuncN::create([&](cocos2d::Node* sender) {
        CCLOG("Complete swap");
        m_pGameStateMachine->enterState<IdleState>();
    });

    auto sequence = cocos2d::Sequence::create(ease1,callback, NULL);
    tile1->runAction(sequence);
    tile2->runAction(ease2);
}

void SwappyGrid::swapTiles(Tile *pTile, cocos2d::Vec2 vec2) {
    cocos2d::Vec2 gridPos1 = screenToGrid(pTile->getPosition());
    cocos2d::Vec2 gridPos2 = gridPos1 + vec2;
    swapTiles(gridPos1, gridPos2);
}


cocos2d::Vec2 SwappyGrid::gridToScreen(cocos2d::Vec2 pos) const {
    return gridToScreen(pos.x, pos.y);
}

cocos2d::Vec2 SwappyGrid::gridToScreen(int x, int y) const {
    return cocos2d::Vec2(
            m_tileSize.width*x,
            m_tileSize.height*y
    );
}

cocos2d::Vec2 SwappyGrid::screenToGrid(cocos2d::Vec2 pos) const {
    return cocos2d::Vec2(
            (int)std::ceil(pos.x/m_tileSize.width),
            (int)std::ceil(pos.y/m_tileSize.height)
    );
}

cocos2d::Vec2 SwappyGrid::getTopOfScreen() const {
    return convertToNodeSpace(cocos2d::Vec2(0, visibleSize.height));
}

int SwappyGrid::getTopOffscreenTileSlot() const {
    return (int)std::ceil((getTopOfScreen().y/m_tileSize.height));
}

int SwappyGrid::insertTileIntoColumn(int columnNumber, Tile *tile, bool fromTop) {
    TileColumn* col = m_pGrid->at(columnNumber);
    col->push_back(tile);
    return col->size()-1;
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
        int numTilesInGridCol = m_pGrid->at(i)->size();
        int numTilesWaitingToDropInCol = m_pTileDropQueues->at(i)->size();
        counts.push_back(NUM_ROWS - numTilesWaitingToDropInCol - numTilesInGridCol);
    }

    return counts;
}

void SwappyGrid::addTileToDropQueue(int column, Tile *pTile) {
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS && column < m_pTileDropQueues->size());
    if(pTile->getGrid() == nullptr) {
        pTile->setGrid(this);
    }
    TileDropQueue* q = m_pTileDropQueues->at(column);
    q->push(pTile);
}

void SwappyGrid::addRandomTileToDropQueue(int column) {
    Tile* tile = level->getRandomTile();
    tile->setGrid(this);

    // Put tile in the correct place
    // but don't drop it yet.
    cocos2d::Vec2 newPos = gridToScreen(column, getTopOffscreenTileSlot());
    tile->setPosition(newPos);
    addChild(tile,2);

    // Drop the random tile in the given column
    // using the drop queue to ensure it only
    // drops when allowed
    addTileToDropQueue(column, tile);

}

bool SwappyGrid::columnReadyToDropTile(int column) {
    /**
     * Loop through all sprites in that column
     * If any are in the top slot, then hold off
     * on dropping any more
     */
    auto fsm = (StateMachine *) m_pColumnStateMachines->at(column);
    for(cocos2d::Sprite* sprite : *m_pGrid->at(1)) {
        auto bb = sprite->getBoundingBox();
        if(bb.containsPoint(gridToScreen(column, getTopOffscreenTileSlot()-1))) {
            fsm->enterState<BusyState>();
            return false;
        }
    }
    fsm->enterState<ColumnReadyToDropState>();
    return true;

//    return colState->canDropTile();
}
