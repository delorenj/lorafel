//
// Created by Jarad M DeLorenzo on 11/28/16.
//

#ifndef LORAFEL_LEVELMANAGER_H
#define LORAFEL_LEVELMANAGER_H

#include "cocos2d.h"
#include "Level.h"

USING_NS_CC;

namespace lorafel {
    class LevelManager : public cocos2d::Ref {
    protected:
        LevelManager() {
            init();
        };

        ~LevelManager() {
            CCLOG("LevelManager::~LevelManager()");
            CC_SAFE_DELETE(m_pLevelTree);
            CC_SAFE_DELETE(m_pTileTree);
        }

        virtual void init();
        static LevelManager* _instance;
        ValueMap* m_pLevelTree;
        ValueMap* m_pTileTree;
        SwappyGrid* m_pSwappyGrid;
        Level* m_pCurrentLevel;

    public:

        static LevelManager* getInstance() {
            if (_instance == nullptr) {
                _instance = new LevelManager();
            }
            return _instance;
        }
        void loadLevelTree(cocos2d::Value data);
        void loadTileTree(cocos2d::Value data);

        ValueMap* getLevelTree() const { return m_pLevelTree; }
        ValueMap* getTileTree() const { return m_pTileTree; }
        Level* getCurrentLevel() const { return m_pCurrentLevel; }
        void setCurrentLevel(Level* level) { m_pCurrentLevel = level; }
        void setSwappyGrid(SwappyGrid* pGrid) { m_pSwappyGrid = pGrid; }
        SwappyGrid* getSwappyGrid() const { return m_pSwappyGrid; }

        Level* createLevel(int levelId);
    };
}

#endif //LORAFEL_LEVELMANAGER_H
