//
// Created by Jarad DeLorenzo on 6/15/16.
//

#ifndef LORAFEL_CHARACTERMODAL_H
#define LORAFEL_CHARACTERMODAL_H

#include "cocos2d.h"

namespace lorafel {
    class CharacterModal : public cocos2d::Node {
    public:
        virtual bool init() override;

        CREATE_FUNC(CharacterModal);

        static CharacterModal* createAndDropIn(cocos2d::Node* container);
        CharacterModal* dismiss(std::function<void(void)> callback);
        cocos2d::Sprite* getWindow() { return m_pWindow; }

    protected:
        cocos2d::Sprite* m_pWindow;
        cocos2d::Size m_visibleSize;
        cocos2d::Vec2 m_origin;
        cocos2d::Sprite* m_pClose;
    };
}

#endif //LORAFEL_CHARACTERMODAL_H
