//
// Created by Jarad DeLorenzo on 12/18/15.
//

#include "SwappyGrid.h"


using namespace lorafel;

bool SwappyGrid::init() {
    tileFactory = TileFactory::getInstance();
    return true;
}

void SwappyGrid::loadLevel(Level *level) {
    //Set the grid's level
    this->level = level;

    // Generate a tile using the TileFactory
    // Pass in the level which includes this
    // level's Tile Distribution
    Tile* tile = tileFactory->getTile(level);

    // The middle column
    int column = NUM_COLUMNS/2;

    // Drop the random tile in the given column
    dropTile(column, tile);
    CC_SAFE_DELETE(tile);
}

void SwappyGrid::dropTile(int column, Tile *tile) {
    // Make sure we're dropping a tile at a valid location
    CC_ASSERT(column >= 0 && column < NUM_COLUMNS);
    tile->setPosition(getColumnDropPosition(column));


}

cocos2d::Vec2 SwappyGrid::getColumnDropPosition(int column) {

}
