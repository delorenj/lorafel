//
// Created by Jarad DeLorenzo on 3/9/16.
//

#include "GridTransparency.h"
#include "Globals.h"

using namespace lorafel;

bool GridTransparency::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }

    return true;
}

void GridTransparency::insertTile(cocos2d::Vec2 pos, GridTransparency::Tile tile) {
    auto node = createTile(tile);
    node->setPosition(pos);
    addChild(node);
}

cocos2d::Sprite* GridTransparency::createTile(GridTransparency::Tile tile) {
    if(tile.getColor() == Tile::Color::NONE) {
        auto s = cocos2d::Sprite::create("Storm.png");
        s->setOpacity(255);
        return s;
    }

    if(tile.getColor() == Tile::Color::LIGHT) {
        auto s = cocos2d::Sprite::create("Storm.png");
        s->setOpacity(150);
        return s;
    }

    if(tile.getColor() == Tile::Color::DARK) {
        auto s = cocos2d::Sprite::create("PoisonGlyph.png");
        s->setOpacity(150);
        return s;
    }
}
