//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "SwappyGrid.h"
#include "GameStateMachine.h"
#include "Level.h"
#include "EnemyTile.h"
#include "PlayerManager.h"
#include "GameOverUI.h"
#include "EventDataTile.h"

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

    /**
     * Create a physics world with no gravity
     */
//    m_pWorld = new b2World(b2Vec2(0, 0));
//    m_pWorld->SetAllowSleeping(false);

    setName("SwappyGrid");

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
    m_tileScaleFactor = (visibleSize.width - 100) / (NUM_COLUMNS * originalTileSize.width);
    m_tileSize = originalTileSize * 1.15;
    setScale(m_tileScaleFactor);

    // Create the debug drawing node
//    m_pDebugDraw = cocos2d::DrawNode::create();
//    m_pDebugDraw->setAnchorPoint(cocos2d::Vec2(0, 0));
//    m_pDebugDraw->setPosition(0, 0);
//    addChild(m_pDebugDraw, LayerOrder::DEBUG);

    // Create the Grid Transparency;
    m_pGridTransparency = new GridTransparency();
    addChild(m_pGridTransparency, LayerOrder::TILES-5);

    // Create Tile Grid
    m_pGrid = new TileGrid();
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        m_pGrid->push_back(new TileColumn(NUM_COLUMNS * 2));
    }

    // Create Tile Drop Queues
    m_pTileDropQueues = new std::vector<TileQueue*>();

    // Create Tile Remove Queues
    // We need a queue so we only remove tiles in one
    // section of the update() loop
    m_pTileRemoveQueue = new TileQueue();

    for (int j = 0; j < NUM_COLUMNS; ++j) {
        m_pTileDropQueues->push_back(new TileQueue());
    }

    setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    setContentSize(cocos2d::Size(m_tileSize.width * NUM_COLUMNS, m_tileSize.height * NUM_ROWS));

    /**
     * Initialize all the events for each inventory item.
     * Can't do this on create because the items get created
     * before the scene starts running and each item
     * needs a reference to the SwappyGrid to handle
     * touch events
     *
     * Wait...maybe not. Gonna try adding the touch events to
     * the slots themselves.
     *
     * Nope...I'm pretty sure that's not the right solution.
     */
    PlayerManager::getInstance()->getPlayer()->getInventory()->addEvents(this);

    CCLOG("tileSize: %f,%f", m_tileSize.width, m_tileSize.height);
    CCLOG("tileSize * NUM_COLUMNS: %f", m_tileSize.width * NUM_COLUMNS);
    CCLOG("grid contentSize: %f,%f", getContentSize().width, getContentSize().height);
    CCLOG("boundingBox: w=%f,h=%f", getBoundingBox().size.width, getBoundingBox().size.height);

    setPosition(
            origin.x + visibleSize.width / 2,
            visibleSize.height / 2
    );

    scheduleUpdate();
    return true;
}

void SwappyGrid::update(float delta) {

//    DrawDebugData();

//    UpdatePhysics(delta);

    RemoveDeadTiles();

    ReplenishTiles();

    DropTiles();

    ProcessMatches();

    ProcessTurnManager();

    ProcessEnemyTurns();
}

void SwappyGrid::DropTiles() {
    for (int k = 0; k < m_pTileDropQueues->size(); k++) {
        TileQueue* queue = m_pTileDropQueues->at(k);
        if (queue->empty()) continue;
        if (!columnReadyToDropTile(k)) continue;
        lorafel::Tile* tile = queue->front();
        queue->pop();
        dropTile(k, tile);
    }
}

void SwappyGrid::RemoveDeadTiles() {
    GET_GAME_STATE
    if (state->getName() != "TileRemovedState") return;

    TileQueue* queue = m_pTileRemoveQueue;

    if (queue->empty() && getNumberOfFallingTiles() == 0) {
        GameStateMachine::getInstance()->setState<IdleState>();
        return;
    }

    while (!queue->empty()) {
        lorafel::Tile* tile = queue->front();
        queue->pop();
        if(tile->getReferenceCount() > 0) tile->release();
        if (tile->getReferenceCount() == 1) removeTile(tile);
    }

    for (auto x = 0; x < NUM_COLUMNS; x++) {
        for (auto y = 0; y < NUM_ROWS; y++) {
            auto tile = getTileAt(x, y);
            if (tile == nullptr) {
                // blank spot. let's fill in the blank
                    lorafel::Tile* nextTileAbove = getNextTileAbove(x, y);

                if (nextTileAbove == nullptr) continue; // nothing to slide down
                m_pGrid->at(x)->at(nextTileAbove->getGridPos().y) = nullptr;
                m_pGrid->at(x)->at(y) = nextTileAbove;
                nextTileAbove->moveToGridPos(x, y);
            }
        }
    }
}

lorafel::Tile* SwappyGrid::getNextTileAbove(int x, int y) const {
    auto numberOfSlotsToSlideDown = 1;
    auto result = getTileAt(x, y + numberOfSlotsToSlideDown);
    while (result == nullptr && y + numberOfSlotsToSlideDown < NUM_ROWS) {
        numberOfSlotsToSlideDown++;
        result = getTileAt(x, y + numberOfSlotsToSlideDown);
    }
    return result;
}

void SwappyGrid::ReplenishTiles() {
    if(m_pActivePlayerTile == nullptr)
        m_pActivePlayerTile = m_pLevel->getTurnManager()->getNextPlayerTile();

    auto counts = getTileVacancyCounts();
    for (int i = 0; i < counts.size(); ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            /**
             * If the current turn is the enemie's turn
             * make sure enemy glyphs drop instead of
             * normal tiles.
             */
            if(m_pActivePlayerTile->getTag() == Tag::ENEMY) {
                auto tile = static_cast<EnemyTile*>(m_pActivePlayerTile);
                addTileToDropQueue(i, tile->getRandomGlyph());
            } else {
                addRandomTileToDropQueue(i);
            }
        }
    }
}

void SwappyGrid::dropTile(int column, Tile* tile) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
    StateMachine* fsm = m_pColumnStateMachines->at((unsigned long) column);
    fsm->enterState<ColumnBusyState>();
    m_pGameStateMachine->enterState<TileFallingState>();
    m_numberOfFallingTiles++;
    int tileRowIndex = insertTileIntoColumn(column, tile);
    float dropTime = (float) (0.5);
    auto move = cocos2d::MoveTo::create(dropTime, gridToScreen(column, tileRowIndex));
    auto easeAction = cocos2d::EaseBounceOut::create(move->clone());

    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        Tile* tile = static_cast<Tile*>(sender);
        SwappyGrid* obj = static_cast<SwappyGrid*>(tile->getParent());

        obj->setNumberOfFallingTiles(obj->getNumberOfFallingTiles() - 1);
        if (tileDropQueuesEmpty() && obj->getNumberOfFallingTiles() == 0) {
            m_pGameStateMachine->enterState<TileQueueEmptyMatchStartState>();
        }
    });

    auto sequence = cocos2d::Sequence::create(easeAction, callback, NULL);

    tile->runAction(sequence);
}

void SwappyGrid::insertTile(cocos2d::Vec2 pos, Tile* tile) {

}

void SwappyGrid::removeTile(cocos2d::Vec2 point) {

}

void SwappyGrid::swapTiles(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2) {

    if (m_pGameStateMachine->getState()->getName() == "IdleState" ||
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
        Tile* tempTile = m_pGrid->at(pos1.x)->at(pos1.y);
        m_pGrid->at(pos1.x)->at(pos1.y) = m_pGrid->at(pos2.x)->at(pos2.y);
        m_pGrid->at(pos2.x)->at(pos2.y) = tempTile;

        if (m_pGameStateMachine->getState()->getName() == "TileSwappingStartState") {
            m_pGameStateMachine->enterState<TileSwappingEndState>();
        } else {
            m_pGameStateMachine->setState<IdleState>();
        }

    });

    auto sequence = cocos2d::Sequence::create(ease1, callback, NULL);
    move1->setTag(SWAPPING_ACTION_TAG);
    tile1->runAction(sequence);
    tile2->runAction(ease2);
}

void SwappyGrid::swapTiles(Tile* pTile, cocos2d::Vec2 vec2) {
    cocos2d::Vec2 gridPos1 = screenToGrid(pTile->getPosition());
    cocos2d::Vec2 gridPos2 = gridPos1 + vec2;
    swapTiles(gridPos1, gridPos2);
}


const cocos2d::Vec2 SwappyGrid::gridToScreen(cocos2d::Vec2 pos) const {
    return gridToScreen((int) pos.x, (int) pos.y);
}

const cocos2d::Vec2 SwappyGrid::gridToScreen(int x, int y) const {
    return cocos2d::Vec2(
            m_tileSize.width * x,
            m_tileSize.height * y
    );
}

const cocos2d::Vec2 SwappyGrid::screenToGrid(cocos2d::Vec2 pos) const {
    return cocos2d::Vec2(
            clamp<int>(ROUND_2_INT(pos.x / m_tileSize.width), 0, 9),
            clamp<int>(ROUND_2_INT(pos.y / m_tileSize.height), 0 , 9)
    );
}

const cocos2d::Vec2 SwappyGrid::getTopOfScreen() const {
    return convertToNodeSpace(cocos2d::Vec2(0, visibleSize.height));
}

const int SwappyGrid::getTopOffscreenTileSlot() const {
    return ROUND_2_INT(getTopOfScreen().y / m_tileSize.height);
}

int SwappyGrid::insertTileIntoColumn(int columnNumber, Tile* tile, bool fromTop) {
    TileColumn* col = m_pGrid->at(columnNumber);
    auto lowest = lowestVacancyInColumn(columnNumber);
    col->at(lowest) = tile;
    return lowest;
}

bool SwappyGrid::overflow() {
    for (auto col : *m_pGrid) {
        if (col->size() > NUM_ROWS) return true;
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
            if (getTileAt(i, j)) {
                count++;
            }
        }

        int numTilesInGridCol = count;
        int numTilesWaitingToDropInCol = m_pTileDropQueues->at(i)->size();
        counts.push_back(NUM_ROWS - numTilesWaitingToDropInCol - numTilesInGridCol);
    }

    return counts;
}

void SwappyGrid::addTileToDropQueue(int column, Tile* pTile) {
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS && column < m_pTileDropQueues->size());
    pTile->setGrid(this);

    // Put tile in the correct place
    // but don't drop it yet.
    cocos2d::Vec2 newPos = gridToScreen(column, getTopOffscreenTileSlot());
    pTile->setPosition(newPos);
    addChild(pTile, LayerOrder::TILES);

    /**
     * If the tile is a PlayerTile,
     * add it to the turn manager
     */
    if (pTile->getTag() == Tag::HERO || pTile->getTag() == Tag::ENEMY) {
        m_pLevel->getTurnManager()->addPlayerTile(pTile);

        if(pTile->getTag() == Tag::ENEMY) {
            auto eventData = new EventDataTile(pTile);
            getEventDispatcher()->dispatchCustomEvent("new_enemy", eventData);
        }

        if(pTile->getTag() == Tag::HERO) {
            PlayerManager::getInstance()->getPlayer()->equipHook();
        }
    }

    // Drop the random tile in the given column
    // using the drop queue to ensure it only
    // drops when allowed
    TileQueue* q = m_pTileDropQueues->at(column);
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
    auto fsm = (StateMachine*) m_pColumnStateMachines->at(column);
    for (int i = 0; i < NUM_COLUMNS; i++) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            auto tile = getTileAt(i, j);
            if (!tile) continue;
            auto bb = tile->getBoundingBox();
            if (bb.containsPoint(gridToScreen(column, getTopOffscreenTileSlot() - 1))) {
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

void SwappyGrid::ProcessMatches() {
    GET_GAME_STATE
    // Checking for matches can happen at a couple of places
    // 1. After all the tiles that are going to fall, are done falling
    // 2. After a user's valid move
    // TODO: Refactor state to have a member function canCheckForMatches(). This may be cleaner
    if (state->getName() != "TileQueueEmptyMatchStartState" &&
            state->getName() != "TileSwappingEndState") {
        return;
    }

    if(state->getName() != "GameOverState" && PlayerManager::getInstance()->getPlayer()->getHp() == 0) {
        onGameOver();
        return;
    }

    auto matches = m_pTileMatcher->findMatches();

    if (matches.size() > 0) {
        if (!m_pMoveStack->empty()) {
            m_pMoveStack->top()->setMatched(true);
        }
        m_pGameStateMachine->enterState<MatchFoundState>();
        for (auto match : matches) {
            match->run();
        }
        GameStateMachine::getInstance()->enterState<IdleState>();
    } else if(!m_pMoveStack->empty() && m_pMoveStack->top()->getTag() == Tag::CONSUMABLE) {
        /**
         * If the player clicked on a consumable, process that
         * as a move here
         */
        GameStateMachine::getInstance()->enterState<IdleState>();

    } else if (!m_pMoveStack->empty() && !m_pMoveStack->top()->isMatched()) {
        // Only revert tiles when no match is found AND the match was
        // initiated by player move. If match initiated by falling tiles
        // then that means the player move was valid and no need to revert
        //
        // Also, now we should check the tile moved to see if it has a
        // property that allows it to move without matches (2/27/16)
        auto playerMove = m_pMoveStack->top();
        if(!getActivePlayerTile()->freelyMovable()) {
            m_pMoveStack->pop();
            playerMove->cancel();
        } else {
            GameStateMachine::getInstance()->enterState<IdleState>();
        }

    } else if (m_pLevel->isCleared()) {
        // Check to see if level is cleared
        // If so, fire off the end level state
        onLevelCleared();
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
    for (auto q : *m_pTileDropQueues) {
        count += q->size();
    }
    return count == 0;
}

unsigned int SwappyGrid::getNumberOfFallingTiles() const {
    return m_numberOfFallingTiles;
}

TileSwapEventData* SwappyGrid::getTileSwapEventData() const {
    return m_pTileSwapEventData;
}

void SwappyGrid::setNumberOfFallingTiles(unsigned int m_numberOfFallingTiles) {
    SwappyGrid::m_numberOfFallingTiles = m_numberOfFallingTiles;
}

lorafel::Tile* SwappyGrid::getTileAt(const cocos2d::Vec2 pos) const {
    if (pos.x >= m_pGrid->size()) {
        return nullptr;
    }

    TileColumn* col = m_pGrid->at(pos.x);
    if (pos.y >= col->size()) {
        return nullptr;
    } else {
        return col->at(pos.y);
    }
}

lorafel::Tile* SwappyGrid::getTileAt(const int x, const int y) const {
    return getTileAt(cocos2d::Vec2(x, y));
}

void SwappyGrid::clearVisitStates() {
    for (int i = 0; i < NUM_COLUMNS; ++i) {
        for (int j = 0; j < NUM_ROWS; ++j) {
            auto tile = getTileAt(i, j);
            if (!tile) continue;
            tile->setVisitColor(Tile::NONE);
            tile->setVisitOrder(0);
        }
    }
}

void SwappyGrid::setLevel(Level* pLevel) {
    m_pLevel = pLevel;
}

Level* SwappyGrid::getLevel() {
    return m_pLevel;
}

int SwappyGrid::lowestVacancyInColumn(int i) {
    lorafel::Tile* tile;
    int j = 0;
    do {
        tile = getTileAt(i, j++);
    } while (tile != nullptr);

    return j - 1;
}

void SwappyGrid::removeTile(lorafel::Tile* tile) {
    if (tile == nullptr) return;
    auto pos = tile->getGridPos();
    m_pGrid->at(pos.x)->at(pos.y) = nullptr;

    /**
     * Don't remove Hero tile. Causes some shit!
     */
    if(tile->getTag() != Tag::HERO) {
        removeChild(tile);
    }
}

void SwappyGrid::addTileToRemoveQueue(lorafel::Tile* pTile) {
    m_pTileRemoveQueue->push(pTile);
}

void SwappyGrid::DrawDebugData() {
    m_pDebugDraw->drawRect(
            cocos2d::Vec2(0, 0),
            cocos2d::Vec2(getContentSize().width, getContentSize().height),
            cocos2d::Color4F::RED);

    m_pDebugDraw->drawLine(cocos2d::Vec2(getAnchorPointInPoints().x, getAnchorPointInPoints().y + 10), cocos2d::Vec2(getAnchorPointInPoints().x, getAnchorPointInPoints().y - 10), cocos2d::Color4F::YELLOW);
    m_pDebugDraw->drawLine(cocos2d::Vec2(getAnchorPointInPoints().x + 10, getAnchorPointInPoints().y), cocos2d::Vec2(getAnchorPointInPoints().x - 10, getAnchorPointInPoints().y), cocos2d::Color4F::YELLOW);
}

int SwappyGrid::getNumberOfRemainingEnemies() {
    return (int) getEnemyTiles().size();
}

std::set<lorafel::Tile*> SwappyGrid::getEnemyTiles() {
    std::set<lorafel::Tile*> enemies;
    for (int i = 0; i < NUM_COLUMNS; i++) {
        for (int j = 0; j < NUM_ROWS; j++) {
            auto t = getTileAt(i, j);
            if (t != nullptr && t->getTag() == Tag::ENEMY) {
                enemies.insert(t);
            }
        }
    }
    return enemies;
}

void SwappyGrid::onLevelCleared() {
    GameStateMachine::getInstance()->enterState<LevelClearedState>();
    CCLOG("YAY!");
}

void SwappyGrid::ProcessTurnManager() {
    GET_GAME_STATE

    /**
     * If the game is in an idle state, it's time to cycle to
     * the next player's turn. If the next turn is the HERO, then
     * stay in IdleState and let the turn take place. If the next
     * turn is the ENEMY, transition to enemy turn state and
     * and don't allow the HERO to make any moves until 'idle' again
     */
    if (state->getName() == "IdleState") {
        /*
         * If it's game over, then there are no more
         * turns to manager
         *
         * If you have no HP left, and game is not yet marked
         * as 'over', then call the onGameOver() method
         */
        if(state->getName() != "GameOverState" && PlayerManager::getInstance()->getPlayer()->getHp() == 0) {
            onGameOver();
            return;
        }

        auto turnManager = m_pLevel->getTurnManager();
        auto tile = turnManager->getNextPlayerTile();
        m_pActivePlayerTile = tile;  // set this for faster access in the game loop
        if (tile->getTag() == Tag::ENEMY) {
//            GameStateMachine::getInstance()->setState<EnemyTurnState>();
            GameStateMachine::getInstance()->setState<BusyState>();
            auto seq = cocos2d::Sequence::create(
                    cocos2d::DelayTime::create(0.8f),
                    cocos2d::CallFunc::create([=](){
                        GameStateMachine::getInstance()->setState<EnemyTurnState>();
                    }),
                    NULL
            );
            cocos2d::Director::getInstance()->getRunningScene()->runAction(seq);
        }
    }
}

void SwappyGrid::ProcessEnemyTurns() {
    GET_GAME_STATE

    /**
     * If the game is in an EnemyTurnState then do enemy stuff.
     * If idle state, then just continue on and wait for the user
     * to make a move.
     */
    if (state->getName() != "EnemyTurnState") {
        return;
    }

    // Ok, so it's enemy time!
    // Let's get the active enemy tile
    auto tile = m_pActivePlayerTile;
    AIStrategy* strategy = tile->getStrategy();
    PlayerMove* playerMove = strategy->apply(tile);
    /**
     * Need this 'cause the enemy never really 'starts' moving
     * a tile - it should just go to move state
     */
    GameStateMachine::getInstance()->enterState<TileTouchMoveState>();
    executePlayerMove(playerMove);
}

void SwappyGrid::executePlayerMove(PlayerMove* pMove) {
    getMoveStack()->push(pMove);
    getMoveStack()->top()->run();
    getLevel()->getTurnManager()->addMove(pMove);
}

lorafel::Tile* SwappyGrid::getActivePlayerTile() {
    return m_pActivePlayerTile;
}

void SwappyGrid::setActivePlayerTile(lorafel::Tile* pTile) {
    m_pActivePlayerTile = pTile;
}

void SwappyGrid::highlightTiles(TileSet* pSet) {
    for (auto tile : *pSet) {
        // Mark tile as valid move distance
        // Not necessarily a valid match though
        tile->setVisitColor(Tile::Color::YELLOW);

        if(tile->getLeft() == nullptr || pSet->find(tile->getLeft()) == pSet->end()) {
            addTileBorderHighlight(pSet, tile, cocos2d::Vec2(tile->getPosition().x, tile->getPosition().y + m_tileSize.height/2), 0);
        }

        if(tile->getTop() == nullptr || pSet->find(tile->getTop()) == pSet->end()) {
            addTileBorderHighlight(pSet, tile, cocos2d::Vec2(tile->getPosition().x + m_tileSize.width/2, tile->getPosition().y + m_tileSize.height), 90);
        }

        if(tile->getBottom() == nullptr || pSet->find(tile->getBottom()) == pSet->end()) {
            addTileBorderHighlight(pSet, tile, cocos2d::Vec2(tile->getPosition().x + m_tileSize.width/2, tile->getPosition().y), 90);
        }

        if(tile->getRight() == nullptr || pSet->find(tile->getRight()) == pSet->end()) {
            addTileBorderHighlight(pSet, tile, cocos2d::Vec2(tile->getPosition().x + m_tileSize.width, tile->getPosition().y + m_tileSize.height/2), 0);
        }
    }
}

void SwappyGrid::addTileBorderHighlight(TileSet* pSet, const lorafel::Tile* tile, cocos2d::Vec2 anchorPos, float rotation) {
    auto p = cocos2d::ParticleSystemQuad::create("glitter_line.plist");
    p->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    p->setTag(Tag::PARTICLE);
    p->setPosition(anchorPos);
    p->setRotation(rotation);
    p->setAutoRemoveOnFinish(true);
    p->setPosVar(cocos2d::Vec2(0, m_tileSize.height-38));
    addChild(p,lorafel::LayerOrder::PARTICLES);
}

cocos2d::DrawNode* SwappyGrid::getDebugDraw() {
    return m_pDebugDraw;
}

TileGrid* SwappyGrid::getGrid() {
    return m_pGrid;
}

lorafel::Tile* SwappyGrid::getRandomEnemy() {
    auto numEnemies = getNumberOfRemainingEnemies();

    if(numEnemies == 0) return nullptr;

    auto enemies = getEnemyTiles();
    TileSet::const_iterator it(enemies.begin());

    if(numEnemies == 1) return *it;

    std::advance(it,std::rand()%(enemies.size()-1));
    return *it;
}

lorafel::Tile* SwappyGrid::getHeroTile() {
    return PlayerManager::getInstance()->getPlayer()->getTile();
}

void SwappyGrid::onGameOver() {
    GameStateMachine::getInstance()->enterState<GameOverState>();

    // Wait a few seconds, and then instantiate the game over screen
    schedule(schedule_selector(SwappyGrid::initGameOverScreen), 1.5);

}

void SwappyGrid::initGameOverScreen(float dt) {
    unschedule(schedule_selector(SwappyGrid::initGameOverScreen));
    auto gameOverUI = GameOverUI::create();
    gameOverUI->show();
}

SwappyGrid::~SwappyGrid() {
    CCLOG("~SwappyGrid()");
    CC_SAFE_DELETE(m_pMoveStack);
    CC_SAFE_DELETE(m_pColumnStateMachines);

    for(auto q : *m_pTileDropQueues) {
        CC_SAFE_DELETE(q);
    }

    CC_SAFE_DELETE(m_pTileRemoveQueue);
    CC_SAFE_DELETE(m_pGrid);
//    CC_SAFE_DELETE(m_pLevel);
    CC_SAFE_DELETE(m_pTileMatcher);
}

GridTransparency* SwappyGrid::getGridTransparency() {
    return m_pGridTransparency;
}

bool SwappyGrid::isPointInsideGrid(cocos2d::Vec2 pos) {
    return getBoundingBox().containsPoint(pos);
}

cocos2d::Size SwappyGrid::getTileSize() {
    return m_tileSize;
}

void SwappyGrid::UpdatePhysics(float delta) {
}
