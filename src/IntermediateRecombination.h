//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_INTERMEDIATERECOMBINATION_H
#define SRES_INTERMEDIATERECOMBINATION_H

#include "CrossOver.h"

namespace opt {

    class IntermediateRecombination  : public CrossOver {

    public:

        using CrossOver::CrossOver;

        ~IntermediateRecombination() override = default;

        void crossover(Individual &parent1, Individual &parent2) override;


    };
}


#endif //SRES_INTERMEDIATERECOMBINATION_H
