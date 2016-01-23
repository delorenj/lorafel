//
// Created by Jarad DeLorenzo on 1/22/16.
//

#include "Floatie.h"
#include "ui/CocosGUI.h"

using namespace lorafel;

bool Floatie::init() {
    return true;
}

bool Floatie::initWithString(const char *string) {
    m_pFloatie = cocos2d::ui::Text::create(string,"fonts/BebasNeue Bold.ttf", 24);
    addChild(m_pFloatie);
    return true;
}

bool Floatie::initWithSprite(const char *spriteName) {
    return nullptr;
}
