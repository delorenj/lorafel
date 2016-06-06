//
// Created by Jarad DeLorenzo on 6/6/16.
//

#ifndef LORAFEL_STUPIDRANDOMIZER_H
#define LORAFEL_STUPIDRANDOMIZER_H


#include "IRandomizerStrategy.h"

namespace lorafel {
    class StupidRandomizer : public IRandomizerStrategy {
    public:
        virtual int randomize(std::vector<int> freqs);
    };
}

#endif //LORAFEL_STUPIDRANDOMIZER_H
