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
    node->setScale(1.15);
    node->setAnchorPoint(cocos2d::Vec2(0,0));
    addChild(node);
}

cocos2d::Sprite* GridTransparency::createTile(GridTransparency::Tile tile) {
    if(tile.getColor() == Tile::Color::NONE) {
        auto s = cocos2d::Sprite::create("light_bg.png");
        s->setOpacity(0);
        return s;
    }

    cocos2d::Sprite* s = nullptr;

    if(tile.getColor() == Tile::Color::LIGHT) {
        switch(tile.getType()) {
            case Tile::Type::TOP_LEFT: {
                s = cocos2d::Sprite::create("tl_light_bg.png");
                break;
            }
            case Tile::Type::NONE: {
                s = cocos2d::Sprite::create("c_light_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_LEFT: {
                s = cocos2d::Sprite::create("bl_light_bg.png");
                break;
            }
            case Tile::Type::BOTTOM: {
                s = cocos2d::Sprite::create("b_light_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_RIGHT: {
                s = cocos2d::Sprite::create("br_light_bg.png");
                break;
            }
            case Tile::Type::RIGHT: {
                s = cocos2d::Sprite::create("r_light_bg.png");
                break;
            }
            case Tile::Type::TOP_RIGHT: {
                s = cocos2d::Sprite::create("tr_light_bg.png");
                break;
            }
            case Tile::Type::TOP: {
                s = cocos2d::Sprite::create("t_light_bg.png");
                break;
            }
            case Tile::Type::LEFT: {
                s = cocos2d::Sprite::create("l_light_bg.png");
                break;
            }
            case Tile::Type::CENTER: {
                s = cocos2d::Sprite::create("c_light_bg.png");
                break;
            }
        }

        s->setOpacity(GridTransparency::opacity);
        return s;
    }

    if(tile.getColor() == Tile::Color::DARK) {
        switch(tile.getType()) {
            case Tile::Type::TOP_LEFT: {
                s = cocos2d::Sprite::create("tl_dark_bg.png");
                break;
            }
            case Tile::Type::NONE: {
                s = cocos2d::Sprite::create("c_dark_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_LEFT: {
                s = cocos2d::Sprite::create("bl_dark_bg.png");
                break;
            }
            case Tile::Type::BOTTOM: {
                s = cocos2d::Sprite::create("b_dark_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_RIGHT: {
                s = cocos2d::Sprite::create("br_dark_bg.png");
                break;
            }
            case Tile::Type::RIGHT: {
                s = cocos2d::Sprite::create("r_dark_bg.png");
                break;
            }
            case Tile::Type::TOP_RIGHT: {
                s = cocos2d::Sprite::create("tr_dark_bg.png");
                break;
            }
            case Tile::Type::TOP: {
                s = cocos2d::Sprite::create("t_dark_bg.png");
                break;
            }
            case Tile::Type::LEFT: {
                s = cocos2d::Sprite::create("l_dark_bg.png");
                break;
            }
            case Tile::Type::CENTER: {
                s = cocos2d::Sprite::create("c_dark_bg.png");
                break;
            }
        }

        s->setOpacity(GridTransparency::opacity);
        return s;
    }
}
