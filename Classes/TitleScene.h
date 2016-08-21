//
// Created by Jarad DeLorenzo on 8/7/16.
//

#ifndef LORAFEL_TITLESCENE_H
#define LORAFEL_TITLESCENE_H

#include <cocos/ui/UIButton.h>
#include "AuthStateMachine.h"

namespace lorafel {
    class TitleScene : public cocos2d::Node {
    public:
        ~TitleScene();

        static cocos2d::Scene* createScene();
        virtual bool init() override;
        CREATE_FUNC(TitleScene);

        virtual void update(float delta) override;
        void loadPlayer(cocos2d::Node* sender, cocos2d::Value data);
        void changeStateSelector(cocos2d::Node* sender, cocos2d::Value data);
        
    protected:
        cocos2d::Sprite* m_pBackground;
        StateMachine* m_pStateMachine;
        cocos2d::ui::Button* m_pPlayButton;
        cocos2d::Sprite* m_pLoader;
        cocos2d::ui::Button* m_pGoogleSignInButton;

        
        
    };
}

#endif //LORAFEL_TITLESCENE_H
