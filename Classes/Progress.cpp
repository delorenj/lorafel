//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Progress.h"

using namespace lorafel;

void Progress::save() {

}

void Progress::load() {

}

void Progress::onLoadComplete(cocos2d::ValueMap data) {
    CCLOG("Progress::onLoadComplete() - Loading player progress");
    if(!data["level_score"].isNull()) {
        auto levelScores = data["level_score"].asIntKeyMap();
        for(auto levelScore : levelScores) {
            int completedLevel = levelScore.first;
            int score = levelScore.second.asInt();
            m_mapLevelScores[completedLevel] = score;
        }

    } else {
        setCurrentWorldId(1);
        setCurrentLevelId(1);
    }

}
