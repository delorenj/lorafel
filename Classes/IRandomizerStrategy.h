//
// Created by Jarad DeLorenzo on 12/20/15.
//

#ifndef LORAFEL_IRANDOMIZERSTRATEGY_H
#define LORAFEL_IRANDOMIZERSTRATEGY_H

#include <vector>

namespace lorafel {
    class IRandomizerStrategy {
    public:
        virtual int randomize(std::vector<int>) = 0;
    };
}

#endif //LORAFEL_IRANDOMIZERSTRATEGY_H
