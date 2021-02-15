//
// Created by Ciaran on 14/02/2021.
//

#include "PointMutation.h"
#include "RandomNumberGenerator.h"
#include <algorithm>
#include <execution>

namespace opt {


    void PointMutation::mutate() {
        std::for_each(std::execution::par, population_->begin(), population_->end(), [&](Individual &ind) {
            double r = RandomNumberGenerator::getInstance().uniformReal(0, 1);
            if (r < pb_) {
                // pick an j index
                int idx = RandomNumberGenerator::getInstance().uniformInt(0, ind.size());
                ind[idx] += RandomNumberGenerator::getInstance().normal(ind[idx], 1);
            }
        });
    }

    PointMutation::PointMutation(double pb)
            : pb_(pb) {}


}



