//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Progress.h"
#include "FirebaseDatabase.h"

using namespace lorafel;

void Progress::save() {

}

void Progress::load() {

}

void Progress::onLoadComplete(cocos2d::ValueMap data) {
    CCLOG("Progress::onLoadComplete() - Loading player progress");
    if(!data["level_score"].isNull()) {
        auto levelScores = data["level_score"].asValueVector();
        std::set<int> completedLevelIds;
        for(auto levelScore : levelScores) {
            int completedLevel = levelScore.first;
            int score = levelScore.second.asInt();
            m_mapLevelScores[completedLevel] = score;
            completedLevelIds.insert(completedLevel);
        }
        /**
         * Refactor this and pull out into method
         */
        setCurrentLevelId((int)*std::max_element(completedLevelIds.begin(), completedLevelIds.end()) + 1);
        setCurrentWorldId(1);

    } else {
        setCurrentLevelId(1);
        setCurrentWorldId(1);
    }

}

Progress *Progress::setLevelScore(int score) {
    setLevelScore(m_currentLevelId, score);
    return this;
}

Progress *Progress::setLevelScore(int levelId, int score) {
    m_mapLevelScores[levelId] = score;
    FirebaseDatabase::getInstance()->setStringForKey(to_string(levelId), to_string(score), "level_score");
    return this;
}
