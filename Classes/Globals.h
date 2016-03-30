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

namespace lorafel {
    #define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))

    static float getAngleToPoint(cocos2d::Vec2 vec2) {
        auto bearingRadians = atan2f(-vec2.y, vec2.x);
        auto bearingDegrees = (float)(bearingRadians * (180 / M_PI));
        while(bearingDegrees < 0) {
            bearingDegrees += 360;
        }
        return bearingDegrees;
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
        static const int HIGHLIGHT = 7;
        static const int CONSUMABLE = 8;
    };

    struct LayerOrder {
        static const int BACKGROUND = 1;
        static const int TILES = 10;
        static const int PARTICLES = 20;
        static const int UX = 30;
        static const int GAMEOVER = 40;
        static const int DEBUG = 100;
    };
}

#endif //LORAFEL_GLOBALS_H
