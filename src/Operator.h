//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_OPERATOR_H
#define SRES_OPERATOR_H

#include "Population.h"

namespace opt {

    /**
     * @brief superclass for all selection, mutation and crossover operators.
     *
     */
    class Operator {

    public:

        Operator() = default;

        explicit Operator(SharedPopulation population);

        explicit Operator(SharedPopulation population, SharedPopulation nextGen);

        [[nodiscard]] const SharedPopulation &getNextGen() const;

        void setNextGen(const SharedPopulation &nextGen);

        [[nodiscard]] const SharedPopulation &getPopulation() const;

        void setPopulation(const SharedPopulation &population);

    protected:

        /**
         * A population of individuals
         */
        SharedPopulation population_;

        /**
         * The next population of individuals. Needed
         * by only some algorithms
         */
        SharedPopulation nextGen_;

    };
}

#endif //SRES_OPERATOR_H
