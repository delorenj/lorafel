//
// Created by Jarad DeLorenzo on 3/1/16.
//

#ifndef LORAFEL_GAMEOVERSCENE_H
#define LORAFEL_GAMEOVERSCENE_H

#include <cocos/ui/UIButton.h>
#include <cocos/ui/UILayout.h>
#include "cocos2d.h"
#include "StateMachine.h"


namespace lorafel {

    class GameOverUI : public cocos2d::Node {
    public:
        virtual bool init();
        CREATE_FUNC(GameOverUI);
        void show();
        void tweenText();

    protected:
        cocos2d::Sprite *pSprBackground;
        cocos2d::ui::Button* m_pResume;
        cocos2d::ui::Layout* m_pLayout;



    };
}

#endif //LORAFEL_GAMEOVERSCENE_H
