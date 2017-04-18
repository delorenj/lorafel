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
//    #define DISABLE_RANDOM_SEED
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
    typedef std::pair<int, int> Coords;
    struct PaginatedCoords {
        int page;
        Coords coords;

        bool operator< (const PaginatedCoords& rhs) const
        {
            if(this->page < rhs.page) {
                return true;
            }
            if(this->page > rhs.page) {
                return false;
            }
            return this->coords < rhs.coords;
        }

        bool operator== (const PaginatedCoords& rhs) const
        {
            return this->coords == rhs.coords && this->page == rhs.page;
        }

    };

    typedef struct PaginatedCoords PaginatedCoords;

    static int generateUniqueId() {
        return cocos2d::RandomHelper::random_int(0, RAND_MAX);
    }

    static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }

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
        static const int CONTENTS = 15;
        static const int STAT_EFFECT = 16;
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

    struct BuffDebuffTag {
        static const int BLESSED = 1;
        static const int NONE = 0;
        static const int POISONED = -1;
    };

    struct AnimationType {
        static const int NONE = 0;
        static const int ONCE = 1;
        static const int CIRCULAR_LOOP = 2;
        static const int REVERSE_LOOP = 3;
        static const int ONCE_FORWARD_ONCE_BACK = 4;
    };
}

#endif //LORAFEL_GLOBALS_H
