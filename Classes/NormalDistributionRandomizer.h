//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_NORMALDISTRIBUTIONRANDOMIZER_H
#define LORAFEL_NORMALDISTRIBUTIONRANDOMIZER_H

#include "IRandomizerStrategy.h"
#include <vector>

namespace lorafel {
    class NormalDistributionRandomizer : public IRandomizerStrategy {
    public:
        virtual u_long randomize(std::vector<int>);
    };
}


#endif //LORAFEL_NORMALDISTRIBUTIONRANDOMIZER_H
