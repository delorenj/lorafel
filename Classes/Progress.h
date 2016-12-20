//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PROGRESS_H
#define LORAFEL_PROGRESS_H

namespace lorafel {

    typedef std::unordered_map<int, int> LevelScoreMap;

    class Progress {

    public:
        int getCurrentLevelId() const { return m_currentLevelId; }
        const void setCurrentLevelId(int levelId) { m_currentLevelId = levelId; }
        int getCurrentWorldId() const { return m_currentWorldId; }
        LevelScoreMap getLevelScoreMap() const { return m_mapLevelScores; }
        int getLevelScore(int levelId) const { return m_mapLevelScores.at(levelId); }
        Progress* setLevelScore(int levelId, int score);
        Progress* setLevelScore(int score);
        void save();
        void load();
        void onLoadComplete(cocos2d::ValueMap data);

    protected:
        const void setCurrentWorldId(int worldId) { m_currentWorldId = worldId; }
        
        LevelScoreMap m_mapLevelScores;
        int m_currentLevelId;
        int m_currentWorldId;
    };

}
#endif //LORAFEL_PROGRESS_H
