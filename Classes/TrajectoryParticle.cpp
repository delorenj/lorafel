//
// Created by Jarad DeLorenzo on 3/22/16.
//

#include "TrajectoryParticle.h"

using namespace lorafel;

bool TrajectoryParticle::init() {
    initWithFile("dashed-line.plist");
    setAnchorPoint(cocos2d::Vec2(0,0));
    setScaleY(0.25f);
    setAutoRemoveOnFinish(true);
    return true;
}
