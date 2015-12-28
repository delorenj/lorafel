//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "SwappyGrid.h"


using namespace lorafel;

bool SwappyGrid::init() {
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // Calculate the Tile size so we know how
    // big to make the grid
    auto spritecache = cocos2d::SpriteFrameCache::getInstance();
    m_tileSize = spritecache->getSpriteFrameByName("avocado.png")->getOriginalSizeInPixels();
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
    this->setPosition(
            origin.x + visibleSize.width/2 - m_tileSize.width*NUM_COLUMNS/2,
            visibleSize.height - maxGridHeight - m_tileSize.height*0.25
    );
    return true;
}

void SwappyGrid::loadLevel(Level *level) {
    //Set the grid's level
    this->level = level;

//    while()
    for(int i=0; i<NUM_COLUMNS; i++) {
        // Generate a tile using the TileFactory
        // Pass in the level which includes this
        // level's Tile Distribution
        Tile* tile = level->getRandomTile();

        // Drop the random tile in the given column
        dropTile(i, tile);
    }
}

void SwappyGrid::dropTile(int column, Tile *tile) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
    tile->setPosition(gridToScreen(column, 0));
    tile->getPhysicsBody()->setVelocity(cocos2d::Vec2(0,-150.0));
    addChild(tile,2);


}

void SwappyGrid::dropTile(int column) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
    Tile* tile = level->getRandomTile();

    // Drop the random tile in the given column
    dropTile(column, tile);
}

void SwappyGrid::addTile(cocos2d::Point pos, Tile *tile) {

}

void SwappyGrid::removeTile(cocos2d::Point point) {

}

void SwappyGrid::swapTiles(cocos2d::Point pos1, cocos2d::Point pos2) {

}

cocos2d::Point SwappyGrid::gridToScreen(cocos2d::Point pos) {
    return gridToScreen(pos.x, pos.y);
}

cocos2d::Point SwappyGrid::screenToGrid(cocos2d::Point pos) {
    return cocos2d::Vec2();
}

cocos2d::Point SwappyGrid::gridToScreen(int x, int y) {
    int screenX = m_tileSize.width*x + m_tileSize.width/2;
    if(y == 0) {

        // special case.
        // off-screen, above grid
        cocos2d::Point topOfScreen = this->convertToNodeSpace(cocos2d::Vec2(0,visibleSize.height));
        return cocos2d::Vec2(
                screenX,
                topOfScreen.y + m_tileSize.height
        );
    } else {
        return cocos2d::Vec2(
                screenX,
                m_tileSize.height*y/2
        );
    }
}
