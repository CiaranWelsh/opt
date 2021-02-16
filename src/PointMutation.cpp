//
// Created by Ciaran on 14/02/2021.
//

#include "PointMutation.h"
#include "RandomNumberGenerator.h"
#include <algorithm>
#include <execution>

namespace opt {

    PointMutation::PointMutation(double pb)
            : pb_(pb) {}

    void PointMutation::mutate() {
        for (auto &ind : (*population_)) {
            for (int gene = 0; gene < ind.size(); gene++) {
                double r = RandomNumberGenerator::getInstance().uniformReal(0, 1);
                if (r < pb_) {
                    // pick an j index
                    // int idx = RandomNumberGenerator::getInstance().uniformInt(0, ind.size() - 1);
                    ind[gene] += RandomNumberGenerator::getInstance().normal(ind[gene], 1);
                }
            }
        }

//        std::for_each(std::execution::par, population_->begin(), population_->end(), [&](Individual &ind) {
//            double r = RandomNumberGenerator::getInstance().uniformReal(0, 1);
//            if (r < pb_) {
//                // pick an j index
//
//                int idx = RandomNumberGenerator::getInstance().uniformInt(0, ind.size()-1);
//                ind[idx] += RandomNumberGenerator::getInstance().normal(ind[idx], 1);
//            }
//        });
    }


}



