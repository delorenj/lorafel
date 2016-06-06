//
// Created by Jarad DeLorenzo on 6/6/16.
//

#include "Globals.h"
#include "StupidRandomizer.h"

using namespace lorafel;


int StupidRandomizer::randomize(std::vector<int> freqs) {
    return (int) (call++ % (freqs.size()));
}

int StupidRandomizer::randomize(unsigned long size) {
    return (call++ % size);
}



