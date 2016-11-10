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

    setCascadeColorEnabled(true);

    return true;
}

void GridTransparency::insertTile(cocos2d::Vec2 pos, GridTransparency::Tile tile) {
    auto node = createTile(tile);
    node->setPosition(pos);
    node->setScale(1.15);
    node->setAnchorPoint(cocos2d::Vec2(0,0));
    node->setCascadeColorEnabled(true);
    addChild(node);
}

cocos2d::Sprite* GridTransparency::createTile(GridTransparency::Tile tile) {
    if(tile.getColor() == Tile::Color::NONE) {
        auto s = cocos2d::Sprite::createWithSpriteFrameName("light_bg.png");
        s->setOpacity(0);
        return s;
    }

    cocos2d::Sprite* s = nullptr;

    if(tile.getColor() == Tile::Color::LIGHT) {
        switch(tile.getType()) {
            case Tile::Type::TOP_LEFT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("tl_light_bg.png");
                break;
            }
            case Tile::Type::NONE: {
                s = cocos2d::Sprite::createWithSpriteFrameName("c_light_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_LEFT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("bl_light_bg.png");
                break;
            }
            case Tile::Type::BOTTOM: {
                s = cocos2d::Sprite::createWithSpriteFrameName("b_light_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_RIGHT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("br_light_bg.png");
                break;
            }
            case Tile::Type::RIGHT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("r_light_bg.png");
                break;
            }
            case Tile::Type::TOP_RIGHT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("tr_light_bg.png");
                break;
            }
            case Tile::Type::TOP: {
                s = cocos2d::Sprite::createWithSpriteFrameName("t_light_bg.png");
                break;
            }
            case Tile::Type::LEFT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("l_light_bg.png");
                break;
            }
            case Tile::Type::CENTER: {
                s = cocos2d::Sprite::createWithSpriteFrameName("c_light_bg.png");
                break;
            }
        }

        s->setOpacity(GridTransparency::opacity);
        s->setCascadeColorEnabled(true);
        return s;
    }

    if(tile.getColor() == Tile::Color::DARK) {
        switch(tile.getType()) {
            case Tile::Type::TOP_LEFT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("tl_dark_bg.png");
                break;
            }
            case Tile::Type::NONE: {
                s = cocos2d::Sprite::createWithSpriteFrameName("c_dark_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_LEFT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("bl_dark_bg.png");
                break;
            }
            case Tile::Type::BOTTOM: {
                s = cocos2d::Sprite::createWithSpriteFrameName("b_dark_bg.png");
                break;
            }
            case Tile::Type::BOTTOM_RIGHT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("br_dark_bg.png");
                break;
            }
            case Tile::Type::RIGHT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("r_dark_bg.png");
                break;
            }
            case Tile::Type::TOP_RIGHT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("tr_dark_bg.png");
                break;
            }
            case Tile::Type::TOP: {
                s = cocos2d::Sprite::createWithSpriteFrameName("t_dark_bg.png");
                break;
            }
            case Tile::Type::LEFT: {
                s = cocos2d::Sprite::createWithSpriteFrameName("l_dark_bg.png");
                break;
            }
            case Tile::Type::CENTER: {
                s = cocos2d::Sprite::createWithSpriteFrameName("c_dark_bg.png");
                break;
            }
        }

        s->setOpacity(GridTransparency::opacity);
        s->setCascadeColorEnabled(true);
        return s;
    }
    
    return nullptr;
}

void GridTransparency::setColor(cocos2d::Color3B color) {
    for(auto t : getChildren()) {
        t->setColor(color);
    }
}
