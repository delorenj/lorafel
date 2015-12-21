//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "SwappyGrid.h"


using namespace lorafel;

bool SwappyGrid::init() {
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    return true;
}

void SwappyGrid::loadLevel(Level *level) {
    //Set the grid's level
    this->level = level;

    for(int i=0; i<NUM_COLUMNS; i++) {
        // Generate a tile using the TileFactory
        // Pass in the level which includes this
        // level's Tile Distribution
        Tile* tile = level->getRandomTile();

        // Drop the random tile in the given column
        dropTile(i, tile);
    }

    for(int i=0; i<NUM_COLUMNS; i++) {
        for(int j=0; j<4; j++) {
            Tile* tile = level->getRandomTile();
            dropTile(cocos2d::Point(i*tile->getContentSize().width, j*tile->getContentSize().height), tile);
        }
    }
}

void SwappyGrid::dropTile(int column, Tile *tile) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
    tile->setPosition(getColumnDropPosition(column));
    addChild(tile,2);
}

void SwappyGrid::dropTile(cocos2d::Point pos, Tile *tile) {
    // Make sure we're dropping a tile at a valid location
    tile->setPosition(pos);
    addChild(tile,2);
}

cocos2d::Vec2 SwappyGrid::getColumnDropPosition(int column) {
    float x = visibleSize.width/NUM_COLUMNS * column + visibleSize.width/NUM_COLUMNS/2;
    return cocos2d::Vec2(origin.x + x, origin.y + visibleSize.height/2);
}
