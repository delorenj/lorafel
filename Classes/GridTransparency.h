//
// Created by Jarad DeLorenzo on 3/9/16.
//

#ifndef LORAFEL_GRIDTRANSPARENCY_H
#define LORAFEL_GRIDTRANSPARENCY_H

#include "cocos2d.h"

namespace lorafel {
    class GridTransparency : public cocos2d::Node {
    public:
        class CC_DLL Tile {
        public:
            enum class Color {
                NONE,
                LIGHT,
                DARK
            };

            enum class Type {
                NONE,
                BOTTOM_LEFT,
                BOTTOM,
                BOTTOM_RIGHT,
                RIGHT,
                TOP_RIGHT,
                TOP,
                TOP_LEFT,
                LEFT,
                CENTER
            };

            Tile() : m_color(Color::NONE), m_type(Type::NONE) { }
            Tile(Color c, Type t) : m_color(c), m_type(t) { }

            Color getColor() const { return m_color; }
            Type getType() const { return m_type; }

        protected:
            Color m_color;
            Type m_type;
        };

        static const GLubyte opacity = 80;

        virtual bool init() override;
        CREATE_FUNC(GridTransparency);

        void setColor(cocos2d::Color3B color);
        virtual void onExit() override {
            cocos2d::Node::onExit();
            removeAllChildrenWithCleanup(true);
        }
        void insertTile(cocos2d::Vec2 pos, GridTransparency::Tile tile);

    protected:
        cocos2d::Sprite* createTile(Tile tile);
    };
}

#endif //LORAFEL_GRIDTRANSPARENCY_H
