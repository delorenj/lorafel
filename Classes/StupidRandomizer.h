//
// Created by Jarad DeLorenzo on 6/6/16.
//

#ifndef LORAFEL_STUPIDRANDOMIZER_H
#define LORAFEL_STUPIDRANDOMIZER_H


#include "IRandomizerStrategy.h"

namespace lorafel {
    class StupidRandomizer : public IRandomizerStrategy {
    public:
        StupidRandomizer() : call(0) { };

        virtual int randomize(std::vector<int> freqs);
        virtual int randomize(unsigned long size);

    protected:
        int call;
    };
}

#endif //LORAFEL_STUPIDRANDOMIZER_H
