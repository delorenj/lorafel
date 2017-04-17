//
// Created by Jarad DeLorenzo on 4/14/17.
//

#ifndef LORAFEL_STATEFFECT_H
#define LORAFEL_STATEFFECT_H

namespace lorafel {
    class StatEffect : public cocos2d::Node {
    public:
        CREATE_FUNC(StatEffect);
        virtual bool init() override;

        void setTotalStatDelta(int delta);
        void setStatEvent(std::string eventName);
        virtual bool start();
        virtual void fireTrigger(float delta);

        void setStatTag(int tag) { m_buffDebuffTag = tag; }
        int getBuffDebuffTag() const { return m_buffDebuffTag; }

    protected:
        int m_buffDebuffTag;
        std::string m_eventName;
        int m_delta;
    };
}

#endif //LORAFEL_STATEFFECT_H
