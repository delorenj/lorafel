//
// Created by Jarad DeLorenzo on 1/23/16.
//

#ifndef LORAFEL_EVENTDATAFLOATIE_H
#define LORAFEL_EVENTDATAFLOATIE_H

#import "EventData.h"

namespace lorafel {
    class EventDataFloatie : public EventData {
    public:
        EventDataFloatie(int data, cocos2d::Vec2 pos) : val(data), origin(pos) {} ;
        const int val;
        const cocos2d::Vec2 origin;
    };
}


#endif //LORAFEL_EVENTDATAFLOATIE_H
