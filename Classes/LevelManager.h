//
// Created by Jarad M DeLorenzo on 11/28/16.
//

#ifndef LORAFEL_LEVELMANAGER_H
#define LORAFEL_LEVELMANAGER_H

namespace lorafel {
    class LevelManager {
    protected:
        LevelManager() {
            init();
        };

        virtual void init();

    public:
        static LevelManager* getInstance() {
            if (_instance == nullptr) {
                _instance = new LevelManager();
            }
            return _instance;
        }

        void loadLevelTree(Value data);
        void loadTileTree(Value data);

    protected:
        static LevelManager* _instance;

        cocos2d::ValueMap m_levelTree;
        cocos2d::ValueMap m_TileTree;
    };
}

#endif //LORAFEL_LEVELMANAGER_H
