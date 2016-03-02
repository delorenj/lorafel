//
// Created by Jarad DeLorenzo on 3/1/16.
//

#ifndef LORAFEL_GAMEOVERSCENE_H
#define LORAFEL_GAMEOVERSCENE_H

#include <cocos/ui/UIText.h>
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


        void showButtons();

        cocos2d::ui::Text* m_gameOverText;
        cocos2d::ui::Text* m_tryAgainText;
        cocos2d::ui::Text* m_quitText;
        cocos2d::ui::Button* m_tryAgainButton;
        cocos2d::ui::Button* m_quitButton;
    };
}

#endif //LORAFEL_GAMEOVERSCENE_H
