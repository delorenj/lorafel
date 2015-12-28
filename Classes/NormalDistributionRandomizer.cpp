//
// Created by Jarad DeLorenzo on 12/22/15.
//

#include "NormalDistributionRandomizer.h"
#include <vector>
#include <random>
#include "cocos2d.h"

using namespace lorafel;

int NormalDistributionRandomizer::randomize(std::vector<int> freqs) {
    std::random_device rd;
    std::mt19937 generator(rd());
    double mean = 10.0;
    double std  = 3.0;
    std::normal_distribution<double> normal(mean, std);

#if 0 // Some debug code to see how numbers are generated
    std::vector<int> nums(10);
    for(int i=0; i<2000; i++) {
        int n = cocos2d::clampf(normal(generator), 0, 10);
        CCLOG("Incrementing %d", n);
        nums[n]++;
    }
    CCLOG("Number of nums: %d", nums.size());
    for(auto i : nums) {
        CCLOG("%d", i);
    }
#endif

    std::vector<int> closest;
    int minDiff = 10;
    int randomFreq = cocos2d::clampf(normal(generator), 0, 10);
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
        std::random_shuffle(closest.begin(), closest.end());
    }
    return closest.at(0);
}