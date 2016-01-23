//
// Created by Jarad DeLorenzo on 1/22/16.
//

#include "XpFloatie.h"

using namespace lorafel;

bool XpFloatie::init(const int val) {
    char* buf = new char[10];
    sprintf(buf, "%d XP", val);
    initWithString(buf);
    scheduleUpdate();
    m_pFloatie->setColor(cocos2d::Color3B::YELLOW);
    m_pTarget = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("XpBar");
    return true;
}

void XpFloatie::update(float dt) {

}
