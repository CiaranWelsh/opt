//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_GENETICALGORITHM_H
#define SRES_GENETICALGORITHM_H

#include "PopulationOptimizer.h"
#include "Selection.h"
#include "Mutation.h"
#include "CrossOver.h"

namespace opt {

    /**
     * @brief general genetic algorithm.
     * @details In genetic algorithms, crossover is the main
     * operator (as opposed to EvolutionaryStrategy where
     * mutation is the main operator). The order of operations
     * in the GeneticAlgorithm is:
     *     selection --> crossover --> mutation
     * Users provide their operators to the GeneticAlgorithm
     * and call the fit method, along with an appropriate cost
     * function.
     */
    class GeneticAlgorithm : PopulationOptimizer {

    public:

        GeneticAlgorithm() = default;

        /**
         * @brief construct a genetic algorithm and use default
         * operators.
         */
        GeneticAlgorithm(
                int popSize, int numGenerations, DoubleVector lowerBounds,
                DoubleVector upperBounds, DoubleVector startingVals,
                Selection* select, Mutation* mutate, CrossOver* replicate);


    };

}

#endif //SRES_GENETICALGORITHM_H
