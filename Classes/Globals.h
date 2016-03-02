//
// Created by Jarad DeLorenzo on 1/23/16.
//

#ifndef LORAFEL_GLOBALS_H
#define LORAFEL_GLOBALS_H

namespace lorafel {
    #define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))

    struct Tag {
        static const int UI = 2;
        static const int TILE = 3;
        static const int HERO = 4;
        static const int ENEMY = 5;
        static const int GLYPH = 6;
        static const int HIGHLIGHT = 7;
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
