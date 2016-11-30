
//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILEFACTORY_H
#define LORAFEL_TILEFACTORY_H


#import "Tile.h"

namespace lorafel {
    class TileFactory {
    protected:
        TileFactory() {
            init();
        };

        virtual void init();

    public:
        static TileFactory* getInstance() {
            if (_instance == nullptr) {
                _instance = new TileFactory();
            }
            return _instance;
        }

        lorafel::Tile* create(cocos2d::ValueMap args);

    protected:
        static TileFactory* _instance;
    };

}


#endif //LORAFEL_TILEFACTORY_H