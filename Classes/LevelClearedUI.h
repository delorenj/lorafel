//
// Created by Jarad M DeLorenzo on 11/21/16.
//

#ifndef LORAFEL_LEVELCLEAREDUI_H
#define LORAFEL_LEVELCLEAREDUI_H


#include <cocos/ui/UIButton.h>
#include <cocos/ui/UILayout.h>
#include <cocos/ui/UIText.h>

namespace lorafel {
    class LevelClearedUI : public cocos2d::Node {
    public:
        virtual bool init() override;
        CREATE_FUNC(LevelClearedUI);
        void show();
        void tweenText();

    protected:
        cocos2d::Sprite *pSprBackground;
        cocos2d::ui::Button* m_pResume;
        cocos2d::ui::Layout* m_pLayout;


        void showButtons();

        cocos2d::Sprite* m_pLevelCleared;
        cocos2d::ui::Text* m_tryAgainText;
        cocos2d::ui::Text* m_nextText;
        cocos2d::ui::Button* m_tryAgainButton;
        cocos2d::ui::Button* m_nextButton;

        void tryAgain(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);
        void nextLevel(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eventType);

    };
}

#endif //LORAFEL_LEVELCLEAREDUI_H
