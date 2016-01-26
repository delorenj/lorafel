//
// Created by Jarad DeLorenzo on 1/21/16.
//

#ifndef LORAFEL_EVENTDATAINTEGER_H
#define LORAFEL_EVENTDATAINTEGER_H

#include "EventData.h"

namespace lorafel {
    class EventDataInteger : public EventData {
    public:
        EventDataInteger(int data) : val(data) {} ;
        const int val;
    };
}

#endif //LORAFEL_EVENTDATAINTEGER_H
