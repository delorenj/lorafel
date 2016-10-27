//
// Created by Jarad M DeLorenzo on 10/26/16.
//

#ifndef LORAFEL_LINEARWEIGHTEDRANDOMIZER_H
#define LORAFEL_LINEARWEIGHTEDRANDOMIZER_H

namespace lorafel {
    class LinearWeightedRandomizer {
    public:
        int randomize(int max, int min=0, double scale=10.0) {
            std::random_device rd;
            std::mt19937 generator(rd());
            double mean = 3.0;
            double std  = 4.0;
            std::normal_distribution<double> normal(mean, std);

            double v;
            do {
                v = std::abs(normal(generator) / scale);
            } while (v >= 1.0);
            auto result = (int)(v * max);
            result = std::max(result, min);
            return result;
        }
    };
}

#endif //LORAFEL_LINEARWEIGHTEDRANDOMIZER_H