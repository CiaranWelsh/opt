//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_CROSSOVER_H
#define SRES_CROSSOVER_H

#include "Operator.h"

namespace opt {

    class CrossOver : public Operator {

    public:
        using Operator::Operator;

        virtual ~CrossOver() = default;

        virtual void crossover(Individual &parent1, Individual &parent2) = 0;

        virtual void crossover() = 0;

    };
}

#endif //SRES_CROSSOVER_H
