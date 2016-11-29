//
// Created by Jarad M DeLorenzo on 11/28/16.
//

#ifndef LORAFEL_LEVELMANAGER_H
#define LORAFEL_LEVELMANAGER_H

#include "cocos2d.h"

USING_NS_CC;

namespace lorafel {
    class LevelManager {
    protected:
        LevelManager() {
            init();
        };

        virtual void init();
        static LevelManager* _instance;
        cocos2d::ValueMap m_levelTree;
        cocos2d::ValueMap m_tileTree;

    public:

        static LevelManager* getInstance() {
            if (_instance == nullptr) {
                _instance = new LevelManager();
            }
            return _instance;
        }
        void loadLevelTree(cocos2d::Value data);

        void loadTileTree(cocos2d::Value data);
    };
}

#endif //LORAFEL_LEVELMANAGER_H
