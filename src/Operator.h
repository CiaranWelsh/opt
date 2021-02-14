//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_OPERATOR_H
#define SRES_OPERATOR_H

#include "Population.h"

namespace opt {

    class Operator {

    public:

        Operator() = default;

        explicit Operator(SharedPopulation population);

        [[nodiscard]] const SharedPopulation &getPopulation() const;

        void setPopulation(const SharedPopulation &population);

    protected:

        SharedPopulation population_;

    };
}

#endif //SRES_OPERATOR_H
