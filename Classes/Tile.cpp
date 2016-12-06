//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include <iostream>
#include "Tile.h"
#include "GameStateMachine.h"
#include "BasicPlayerMove.h"
#include "StringPatch.h"
#include "PlayerManager.h"
#include "Level.h"
#include "Globals.h"
#include "LootFactory.h"
#include "SwappyGridScene.h"
#include "XpStatResult.h"

using namespace lorafel;

bool lorafel::Tile::init(cocos2d::ValueMap args) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }
    m_arguments = args;
    m_pStatResults = new std::set<StatResult*>();
    m_pLoot = new TileConfigs();
    setTag(Tag::TILE);
    retain();

    std::string image = m_arguments["tile_image"].isNull() ?
            "close-modal-x.png" : m_arguments["tile_image"].asString();

    std::string tileName = m_arguments["name"].isNull() ?
            "BaseTile" : m_arguments["name"].asString();

    int xp = m_arguments["xp"].isNull() ?
            0 : m_arguments["xp"].asInt();

    if(xp > 0) {
        addStatResult(new XpStatResult(xp));
    }

    initWithSpriteFrameName(image);
    setTileName(tileName);
    initOptions();
    addEvents();

    return true;
}


const std::string& lorafel::Tile::getTileName() const{
    return m_tileName;
}

void lorafel::Tile::setTileName(const std::string name) {
    m_tileName = name;
}
void lorafel::Tile::initOptions() {
    setVisitColor(NONE);
    setAnchorPoint(cocos2d::Vec2(0,0));
    setScale(1.15);
}


void lorafel::Tile::setGrid(SwappyGrid *pGrid) {
    m_pSwappyGrid = pGrid;
}

SwappyGrid* lorafel::Tile::getGrid() {
    return m_pSwappyGrid;
}

void lorafel::Tile::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->isBusy() || dynamic_cast<AttackState*>(state)) {
            return false;
        }

        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = this->getBoundingBox();
        m_pSwappyGrid->setCurrentTouchId(touch->_ID);

        if(rect.containsPoint(p))
        {
            GameStateMachine::getInstance()->enterState<TileTouchStartState>();
            auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTouchStartPos(p);
            touchState->setTileStartPos(getPosition());
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if("TileTouchStartState" == touchState->getName()) {
            auto tilePos = touchState->getTileStartPos();
            auto touchPos = touchState->getTouchStartPos();
            GameStateMachine::getInstance()->enterState<TileTouchMoveState>();
            touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTileStartPos(tilePos);
            touchState->setTouchStartPos(touchPos);
        }
        if("TileTouchMoveState" == touchState->getName()) {
            cocos2d::Vec2 swapVec = getSwapVec(touch);
            if(swapVec.isZero()) return;
            auto swapFrom = m_pSwappyGrid->screenToGrid(touchState->getTileStartPos());
            auto swapTo = m_pSwappyGrid->screenToGrid(touchState->getTileStartPos())+swapVec;

            if(swapTo.x < 0 || swapTo.y < 0 || swapTo.x > SwappyGrid::NUM_COLUMNS || swapTo.y > SwappyGrid::NUM_ROWS) {
                return;
            }
            auto playerMove = new BasicPlayerMove(m_pSwappyGrid, swapFrom, swapTo);
            if (playerMove->isValid()) {
                m_pSwappyGrid->executePlayerMove(playerMove);
            }
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if(touchState->getName() == "TileTouchMoveState") {
            GameStateMachine::getInstance()->enterState<IdleState>();
            auto move = cocos2d::MoveTo::create(0.2, touchState->getTileStartPos());
            runAction(move);
        } else if(touchState->getName() == "TileTouchStartState") {
            GameStateMachine::getInstance()->enterState<IdleState>();
        }
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

cocos2d::Vec2 lorafel::Tile::getSwapVec(cocos2d::Touch *pTouch) {
    auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();

    cocos2d::Vec2 delta = _parent->convertToNodeSpace(pTouch->getLocation()) - touchState->getTouchStartPos();
    float thresh = getContentSize().width*1.15/2;
    bool horizontal = std::abs(delta.x) > std::abs(delta.y);
    if (horizontal && delta.x > thresh) {
        return cocos2d::Vec2(1, 0);
    } else if (horizontal && delta.x < -thresh) {
        return cocos2d::Vec2(-1, 0);
    } else if(horizontal) {
        setPosition(touchState->getTileStartPos().x + delta.x, getPosition().y);
    }

    else if (!horizontal && delta.y < -thresh) {
        return cocos2d::Vec2(0, -1);
    } else if (!horizontal && delta.y > thresh) {
       return cocos2d::Vec2(0, 1);
    } else if(!horizontal) {
        setPosition(getPosition().x, touchState->getTileStartPos().y + delta.y);

    }
    return cocos2d::Vec2(0,0);
}


lorafel::Tile * lorafel::Tile::getLeft(TileGrid *pGrid) const {
    auto pos;
    if(pGrid == nullptr) {
        pos = getGridPos();
        if(pos.x == 0) return nullptr;
    }

    return m_pSwappyGrid->getTileAt(pos.x -1, pos.y, pGrid);
}

lorafel::Tile* lorafel::Tile::getTop() const {
    auto pos = getGridPos();
    if(pos.y == SwappyGrid::NUM_ROWS-1) return nullptr;
    return m_pSwappyGrid->getTileAt(pos.x, pos.y+1);

}

lorafel::Tile* lorafel::Tile::getBottom() const {
    auto pos = getGridPos();
    if(pos.y == 0) return nullptr;
    return m_pSwappyGrid->getTileAt(pos.x, pos.y-1);
}

lorafel::Tile* lorafel::Tile::getRight() const {
    auto pos = getGridPos();
    if(pos.x == SwappyGrid::NUM_COLUMNS-1) return nullptr;
    return m_pSwappyGrid->getTileAt(pos.x+1, (pos.y));
}

const cocos2d::Vec2 lorafel::Tile::getGridPos() const {
    /**
     * Loot animations require a middle-bottom anchor
     * point to scale properly. We need to take that
     * into account when getting the tile column
     */
    auto ap = getAnchorPoint();

    CCASSERT(ap == cocos2d::Vec2::ANCHOR_BOTTOM_LEFT || ap == cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM, "Tile anchor point not supported");

    if(ap == cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM) {
        return m_pSwappyGrid->screenToGrid(cocos2d::Vec2(getPosition().x - getContentSize().width/2, getPosition().y));
    } else{
        return m_pSwappyGrid->screenToGrid(getPosition());
    }
}

std::string lorafel::Tile::getVisitCountAsString() {
    return lorafel::to_string(m_firstVisit);
}

void lorafel::Tile::remove() {
    auto explode = cocos2d::ParticleSystemQuad::create("break_block_color_smoke.plist");
    explode->setAutoRemoveOnFinish(true);
    explode->setScale(0.75);
    explode->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(explode, LayerOrder::PARTICLES);
    setVisible(false);
    m_pSwappyGrid->addTileToRemoveQueue(this);
}

void lorafel::Tile::moveToGridPos(int x, int y) {
    m_pSwappyGrid->setNumberOfFallingTiles(m_pSwappyGrid->getNumberOfFallingTiles()+1);
    auto move = cocos2d::MoveTo::create(0.5, m_pSwappyGrid->gridToScreen(x,y));
    auto ease = cocos2d::EaseBounceOut::create(move->clone());

    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        m_pSwappyGrid->setNumberOfFallingTiles(m_pSwappyGrid->getNumberOfFallingTiles()-1);

    });

    auto sequence = cocos2d::Sequence::create(ease,callback, NULL);
    this->runAction(sequence);

}

void lorafel::Tile::onMatch(Match *pMatch) {
    /**
     * First, check to see if a tile was marked
     * for replacement. If so, we will swap the
     * tile out instead of removing it.  We will
     * then show a glowy around it if the new tile
     * is valuable. Wait, perhaps the glowy should
     * be added at the tile level instead of the
     * match level.
     */
    auto tilesToReplace = pMatch->getTilesToReplace();
    auto iter = tilesToReplace->find(this);
    if(iter != tilesToReplace->end()) {
        CCLOG("Replacing tile with %s", iter->second->getTileName().c_str());
        auto gridPos = getGridPos();
        iter->second->setPosition(iter->first->getPosition());

        /**
         * Add new tile to grid in place of other one
         */
        m_pSwappyGrid->addChild(iter->second, LayerOrder::TILES);

        /**
         * Add new tile to the grid data structure in place of other one
         */
        m_pSwappyGrid->getGrid()->at((unsigned long) gridPos.x)->at((unsigned long) gridPos.y) = iter->second;

        /**
         * Remove the old tile from the screen
         * but mark the grid entry to NOT be deleted
         * on the tile cleanup loop because there will
         * be the replaced tile there! I don't like this
         * 'cause it's weird, but it's how it is.
         */
        iter->first->setTag(Tag::TILE_DONT_REMOVE_FROM_GRID);
        m_pSwappyGrid->removeChild(iter->first);

    } else {
        remove();
    }
}

int lorafel::Tile::getRandHit(lorafel::Tile* pTile) {
    Player* player;
    player = PlayerManager::getInstance()->getPlayer();
    return 10;
}

bool lorafel::Tile::freelyMovable() {
    return false;
}

void lorafel::Tile::showTrajectoryLine(cocos2d::Vec2 dest) {
    /**
     * We need to keep the clipping area an exact square for the case
     * where either x or y is close to zero on either axis. This will
     * cause everything to be clipped and we never want that.
     */
    auto clippingSize = cocos2d::Size(
            2*std::max(std::abs(convertToNodeSpace(dest).x),std::abs(convertToNodeSpace(dest).y)),
            2*std::max(std::abs(convertToNodeSpace(dest).x),std::abs(convertToNodeSpace(dest).y))
    );

    /**
     * Only create the clipping mask and the trajectory
     * line the first time.
     */
    if(m_pClippingMask == nullptr) {
        m_pClippingMask = cocos2d::ClippingRectangleNode::create();
        m_pClippingMask->setPosition(TILE_CENTER);
        m_pClippingMask->setClippingRegion(cocos2d::Rect(cocos2d::Vec2(0,0), clippingSize));
        m_pClippingMask->setContentSize(clippingSize);
        m_pClippingMask->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
        m_pSwappyGrid->addChild(m_pClippingMask,LayerOrder::PARTICLES);
    }

    if(m_pTrajectoryLine == nullptr) {
        m_pTrajectoryLine = TrajectoryParticle::create();
        m_pTrajectoryLine->setAnchorPoint(cocos2d::Vec2(0,0.5f));
        m_pTrajectoryLine->setPosition(cocos2d::Vec2(clippingSize.width/2,clippingSize.height/2));
        m_pClippingMask->addChild(m_pTrajectoryLine,LayerOrder::PARTICLES);
        /**
         * Fast-forward the particle system to make it seem there are
         * many particles to begin with
         */
        for(int i=0; i<300; i++) m_pTrajectoryLine->update(0.1);
    }

    /**
     * We now need to calculate the trajectory line angle and the clipping
     * area based on the current finger position (dest). Since the line is
     * a child of the clipping area, we also need to position the line each
     * time the clipping size is recalculated.
     */
    m_pClippingMask->setClippingRegion(cocos2d::Rect(cocos2d::Vec2(0,0), clippingSize));
    m_pClippingMask->setContentSize(clippingSize);
    m_pTrajectoryLine->setPosition(cocos2d::Vec2(clippingSize.width/2,clippingSize.height/2));
    m_pTrajectoryLine->setRotation(getAngleToPoint(cocos2d::Node::convertToNodeSpace(dest)));
}

void lorafel::Tile::hideTrajectoryLine() {
    if(m_pTrajectoryLine != nullptr) {
        m_pTrajectoryLine->stopSystem();
        m_pTrajectoryLine->setVisible(false);
        m_pTrajectoryLine->setDuration(0.01f);
    }
    m_pTrajectoryLine = nullptr;
    m_pClippingMask = nullptr;
}

void lorafel::Tile::setGlow(const int color) {
    auto particle = cocos2d::ParticleSystemQuad::create("glow_puff.plist");
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(TILE_CENTER);
    particle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);
    particle->setScale(1);
    particle->setTag(Tag::GLOW);

    switch(color) {
        case Glow::BLUE:
            particle->setStartColor(cocos2d::Color4F(0.2051, 0.5098, 0.9241, 0.6753));
            particle->setEndColor(cocos2d::Color4F(0.5413, 0.7108, 0.9834, 0.0844));
            break;
        case Glow::YELLOW:
            particle->setStartColor(cocos2d::Color4F(0.9241, 0.8467, 0.0, 0.6753));
            particle->setEndColor(cocos2d::Color4F(0.9826, 0.9553, 0.6468, 0.0844));
            break;
        case Glow::PURPLE:
            particle->setStartColor(cocos2d::Color4F(0.9185, 0.3721, 0.9236, 0.6753));
            particle->setEndColor(cocos2d::Color4F(0.9830, 0.6343, 0.9829, 0.0844));
            break;
        case Glow::GREEN:
        default:
            particle->setStartColor(cocos2d::Color4F(0.0, 0.9039, 0.2169, 0.6753));
            particle->setEndColor(cocos2d::Color4F(0.6941, 0.9779, 0.7418, 0.0844));
            break;
    };

    removeChildByTag(Tag::GLOW);
    addChild(particle);
    setGlobalZOrder(LayerOrder::PARTICLES+1);

}

lorafel::Tile* lorafel::Tile::generateLootTile() {
    return LootFactory::getInstance()->createTile(this);
}

lorafel::Tile::TileConfigs* lorafel::Tile::getLoot() {
    return m_pLoot;
}

void lorafel::Tile::onHooked() {
    auto swappyGridScene = static_cast<SwappyGridScene*>(m_pSwappyGrid->getParent());
    auto ui = swappyGridScene->getGridUI();
    auto xpBar = static_cast<XpUI*>(ui->getChildByName("XpBar"));
    auto xpBarPos = xpBar->getPosition();

    setAnchorPoint(cocos2d::Vec2(0.5,0));
    setPosition(cocos2d::Vec2(getPosition().x + m_pSwappyGrid->getTileSize().width/2, getPosition().y));

    auto scale = cocos2d::ScaleBy::create(0.9f, 1.5);
    auto scaleEase = cocos2d::EaseElasticOut::create(scale->clone());
    auto hover = cocos2d::MoveBy::create(0.9f, cocos2d::Vec2(0, 15.0f));
    auto initialPopAndScale = cocos2d::Spawn::createWithTwoActions(scaleEase, hover);
    auto delay = cocos2d::DelayTime::create(0.1f);
    auto moveAndAddToInventory = cocos2d::MoveTo::create(0.75f, m_pSwappyGrid->convertToNodeSpace(cocos2d::Vec2(
            xpBarPos.x+xpBar->getContentSize().width/2,
            xpBarPos.y-getContentSize().height))
    );
    auto moveAndAddToInventoryEase = cocos2d::EaseSineInOut::create(moveAndAddToInventory->clone());

    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        auto tile = static_cast<lorafel::Tile*>(sender);

        /**
         * Check to see if this tile implements the Inventoryable
         * interface. If it does, then invoke the addToInventory()
         * method.
         */
        auto inventoryable = dynamic_cast<IInventoryable*>(tile);
        if(inventoryable != nullptr) {
            inventoryable->addToInventory();
        }

        /**
         * After checking to make sure we inventory
         * the tile if it's a loot tile, only then
         * may we delete the tile.
         */
        tile->remove();

        GameStateMachine::getInstance()->setState<TileRemovedState>();
    });

    auto sequence = cocos2d::Sequence::create(
            initialPopAndScale,
            delay,
            moveAndAddToInventoryEase,
            callback,
            NULL
    );

    /**
     * Need to remove tile from grid before animation starts
     * because the grid location is mapped by the current
     * physical location on the SwappyGrid
     */
    GameStateMachine::getInstance()->setState<WaitForAnimationState>();
    m_pSwappyGrid->removeTileFromGrid(this);
    runAction(sequence);
}





