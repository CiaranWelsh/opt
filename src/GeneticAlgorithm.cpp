//
// Created by Ciaran on 13/02/2021.
//

#include "GeneticAlgorithm.h"


namespace opt {

    GeneticAlgorithm::GeneticAlgorithm(
            CostFunction cost, int populationSize, int numGenerations, const DoubleVector& startingVals,
            const DoubleVector& lowerBounds, const DoubleVector& upperBounds,
            Selection *select, Mutation *mutate, CrossOver *crossOver, int childrate,
            bool logspace, bool verbose,
            int numLHSInitSamples, int numGenForLHSInitSamples)
            : PopulationOptimizer(cost, populationSize, numGenerations, startingVals,
                                  lowerBounds, upperBounds, select,
                                  mutate, crossOver){}

    void GeneticAlgorithm::fit() {
        RandomNumberGenerator rng = RandomNumberGenerator::getInstance();
//        Population population = rng.lhs(population)
    }

}