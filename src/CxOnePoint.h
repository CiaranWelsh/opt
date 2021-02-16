//
// Created by Ciaran on 14/02/2021.
//

#ifndef OPT_CXONEPOINT_H
#define OPT_CXONEPOINT_H

#include "CrossOver.h"

namespace opt {

    /**
     * Two parents create two children by selecting a single
     * index j in 0 ... nparam. The two vectors are
     * swapped from that point.
     * For example, the vectors
     *  v1 = {0, 1, 2, 3, 4}
     *  v2 = {5, 6, 7, 8, 9}
     * swapped from index 2 look like this:
     *
     *  v1 = {0, 1, 7, 8, 9}
     *  v2 = {5, 6, 2, 3, 4}
     */
    class CxOnePoint : public CrossOver {
    public:
        using CrossOver::CrossOver;

        void crossover(Individual &parent1, Individual &parent2) override;

        void crossover() override;
    };
}


#endif //OPT_CXONEPOINT_H
