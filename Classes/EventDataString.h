//
// Created by Jarad DeLorenzo on 4/23/16.
//

#ifndef LORAFEL_EVENTDATASTRING_H
#define LORAFEL_EVENTDATASTRING_H

#include "EventData.h"

namespace lorafel {
    class EventDataString : public EventData {
    public:
        EventDataString(const char* data) : val(data) {} ;
        const char* val;
    };
}

#endif //LORAFEL_EVENTDATASTRING_H
