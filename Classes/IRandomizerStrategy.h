//
// Created by Jarad DeLorenzo on 12/20/15.
//

#ifndef LORAFEL_IRANDOMIZERSTRATEGY_H
#define LORAFEL_IRANDOMIZERSTRATEGY_H

#include "Level.h"

namespace lorafel {
    class IRandomizerStrategy {
    public:
        virtual int randomize(std::list<float>) = 0;
    };
}

#endif //LORAFEL_IRANDOMIZERSTRATEGY_H
