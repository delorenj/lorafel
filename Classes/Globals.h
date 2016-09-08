//
// Created by Jarad DeLorenzo on 1/23/16.
//

#ifndef LORAFEL_GLOBALS_H
#define LORAFEL_GLOBALS_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "cocos2d.h"

extern "C" {
    int	 atoi(const char *);
};

/**
 * Some fucked up shit where COCOS2D_DEBUG=1 will
 * not get set
 */
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//#define CCLOG(format, ...)      cocos2d::log(format, ##__VA_ARGS__)
//#endif

namespace lorafel {
    #define DISABLE_RANDOM_SEED 1
    #define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))
    #define DISTRIBUTE(idx, total, size) ((float)size/(2*total) * (1+2*idx))
    #define PTM_RATIO 300.0f  // Pixels-to-Meters

    static float getAngleToPoint(cocos2d::Vec2 vec2) {
        auto bearingRadians = atan2f(-vec2.y, vec2.x);
        auto bearingDegrees = (float)(bearingRadians * (180 / M_PI));
        while(bearingDegrees < 0) {
            bearingDegrees += 360;
        }
        return bearingDegrees;
    }

    static const std::pair<int, int> NULL_COORDINATES = std::make_pair(-1,-1);

    static cocos2d::Rect getMinimumSpanningRect(cocos2d::Sprite* p1, cocos2d::Sprite* p2) {
        auto bb1 = p1->getBoundingBox();
        auto bb2 = p2->getBoundingBox();
        auto pos1 = cocos2d::Director::getInstance()->getRunningScene()->convertToWorldSpace(p1->getPosition());
        auto pos2 = cocos2d::Director::getInstance()->getRunningScene()->convertToWorldSpace(p2->getPosition());
        CCLOG("p1=%f,%f | p2=%f,%f", pos1.x, pos1.y, pos2.x, pos2.y);
        bb1.merge(bb2);
        return bb2;
    }

    static float distribute(int idx, int total, float size) {
        return size/(2*total) * (1+2*idx);
    }

    static int parseInt(const std::string& value)
    {
        // Android NDK 10 doesn't support std::stoi a/ std::stoul
        #if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
            return std::stoi(value);
        #else
            return atoi(value.c_str());
        #endif
    }

    template <typename T>
    T clamp(const T& n, const T& lower, const T& upper) {
        return std::max(lower, std::min(n, upper));
    }

    struct Tag {
        static const int UI = 2;
        static const int TILE = 3;
        static const int HERO = 4;
        static const int ENEMY = 5;
        static const int GLYPH = 6;
        static const int PARTICLE = 7;
        static const int CONSUMABLE = 8;
        static const int LOOT = 9;
        static const int GLOW = 10;
        static const int TOGGLE_ACTION_TILE = 11;
        static const int HOOKABLE_BODY = 12;
        static const int ARROW = 13;
        static const int TILE_DONT_REMOVE_FROM_GRID = 14;
    };

    struct LayerOrder {
        static const int BACKGROUND = 1;
        static const int TILES = 10;
        static const int HERO_TILE = 20;
        static const int PARTICLES = 30;
        static const int UX = 40;
        static const int GAMEOVER = 50;
        static const int DEBUG = 1000;
        static const int MODAL = 10000;
    };

    struct Glow {
        static const int NONE = 0;
        static const int GREEN = 1;
        static const int BLUE = 2;
        static const int PURPLE = 3;
        static const int YELLOW = 4;
    };

}

#endif //LORAFEL_GLOBALS_H
