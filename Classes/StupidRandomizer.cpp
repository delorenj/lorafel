//
// Created by Jarad DeLorenzo on 6/6/16.
//

#include "StupidRandomizer.h"

using namespace lorafel;

int StupidRandomizer::randomize(std::vector<int> freqs) {
    std::random_device rd;
    std::srand((unsigned int) std::time(0));
    std::vector<int> closest;
    int minDiff = 10;
    int randomFreq = (int) cocos2d::clampf(std::rand(), 0, 10);

    for (int j = 0; j < freqs.size(); ++j) {
        int thisDiff = abs(freqs.at(j)-randomFreq);
        if(thisDiff == minDiff) {
            closest.push_back(j);
        } else if(thisDiff < minDiff) {
            minDiff = thisDiff;
            closest.clear();
            closest.push_back(j);
        }
    }

    if(closest.size() > 1) {
        std::shuffle(closest.begin(), closest.end(), rd);
    }
    return closest.at(0);
}

