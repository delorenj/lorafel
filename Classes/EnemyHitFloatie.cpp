#include "EnemyHitFloatie.h"

using namespace lorafel;

bool EnemyHitFloatie::init(const int val) {
    char* buf = new char[10];
    sprintf(buf, "%d HP", val);
    initWithString(buf);

    cocos2d::Label* l = static_cast<cocos2d::Label*>(m_pFloatie);
    l->setColor(cocos2d::Color3B::BLUE);
    l->enableGlow(cocos2d::Color4B::YELLOW);
    l->enableOutline(cocos2d::Color4B::BLACK);

    auto move = cocos2d::MoveBy::create(1, cocos2d::Vec2(0,60));
    auto fade = cocos2d::FadeOut::create(0.7);

    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        EnemyHitFloatie* floatie = static_cast<EnemyHitFloatie*>(sender);
        floatie->removeFromParentAndCleanup(true);
    });
    auto seq = cocos2d::Sequence::create(move, fade, callback, NULL);
    m_pFloatie->runAction(seq);
    return true;

}
