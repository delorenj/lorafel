//
// Created by Jarad DeLorenzo on 1/22/16.
//

#include "Floatie.h"

using namespace lorafel;

bool Floatie::init() {
    return true;
}

bool Floatie::initWithString(const char *string) {
//    m_pFloatie = cocos2d::ui::Text::create(string,"fonts/BebasNeue Bold.ttf", 28);
    m_pFloatie = cocos2d::Label::createWithTTF(string, "fonts/BebasNeue Bold.ttf", 28);
    addChild(m_pFloatie,1);
    return true;
}

bool Floatie::initWithSprite(const char *spriteName) {
    return nullptr;
}
