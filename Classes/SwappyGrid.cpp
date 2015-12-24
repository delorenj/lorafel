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
    auto gridWidth = std::floorf((origin.x + visibleSize.width)*(0.9));
    auto tileWidth = gridWidth/NUM_COLUMNS;
    m_tileScaleFactor = m_tileSize.width/tileWidth;

    // Physics Bounds
    auto body = cocos2d::PhysicsBody::createEdgeSegment(cocos2d::Vec2(origin.x,origin.y),cocos2d::Vec2(origin.x + visibleSize.width,origin.y), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = cocos2d::Node::create();
    edgeNode->setPhysicsBody(body);
    addChild(edgeNode);

    // Create Tile Grid
    m_pGrid = new TileGrid();
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
        tile->setScale(m_tileScaleFactor);

        // Drop the random tile in the given column
        dropTile(i, tile);
    }
}

void SwappyGrid::dropTile(int column, Tile *tile) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
//    tile->setPosition(gridToScreen(column, 0));
    tile->setPosition(getColumnDropPosition(column));
    tile->getPhysicsBody()->setVelocity(cocos2d::Vec2(0,-150.0));
    addChild(tile,2);


}

cocos2d::Vec2 SwappyGrid::getColumnDropPosition(int column) {
    return cocos2d::Vec2(origin.x + m_tileSize.width*column*m_tileScaleFactor + m_tileSize.width*m_tileScaleFactor/2, origin.y + visibleSize.height + 100);
}

void SwappyGrid::addTile(cocos2d::Point pos, Tile *tile) {

}

void SwappyGrid::removeTile(cocos2d::Point point) {

}

void SwappyGrid::swapTiles(cocos2d::Point pos1, cocos2d::Point pos2) {

}

cocos2d::Point SwappyGrid::gridToScreen(cocos2d::Point pos) {
    return cocos2d::Vec2();
}

cocos2d::Point SwappyGrid::screenToGrid(cocos2d::Point pos) {
    return cocos2d::Vec2();
}

cocos2d::Point SwappyGrid::gridToScreen(int x, int y) {
    return cocos2d::Vec2();
}
