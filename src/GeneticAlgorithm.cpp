//
// Created by Ciaran on 13/02/2021.
//

#include <iostream>
#include "GeneticAlgorithm.h"


namespace opt {

    GeneticAlgorithm::GeneticAlgorithm(
            CostFunction cost, int populationSize, int numGenerations, const DoubleVector &startingVals,
            const DoubleVector &lowerBounds, const DoubleVector &upperBounds,
            Selection *select, Mutation *mutate, CrossOver *crossOver,
            bool logspace, bool verbose,
            int numLHSInitSamples, int numGenForLHSInitSamples)
            : PopulationOptimizer(cost, populationSize, numGenerations, startingVals,
                                  lowerBounds, upperBounds, select,
                                  mutate, crossOver) {
        population_ = std::make_shared<Population>(
                Population::fromLHS(populationSize_, optItems_.size(),
                                    startingVals, lowerBounds, upperBounds, logspace_));
        nextGen_ = std::make_shared<Population>(Population(populationSize, optItems_.size()));

    }

    void GeneticAlgorithm::fit() {
        selection_->setPopulation(population_);
        mutation_->setPopulation(population_);
        crossover_->setPopulation(population_);
        for (int i = 0; i < numGenerations_; i++) {
            population_->evaluate(cost_);
            bestFitnessValue_ = (*population_)[0].getFitness();
            std::cout << "Current gen: " << i << "; best fitness: " << bestFitnessValue_
                << "\t\t; x: " << (*population_)[0][0] << "\t\t; y: " <<(*population_)[0][1] << std::endl;

            // select from the population. How many is determined by the
            // howMany variable in the selection operator.
            // select should resize the population to selected individuals only
            selection_->select();

            // mate the selected population
            crossover_->crossover();

            // mutate the selected population
            mutation_->mutate();

            // resize back to original size.
            population_->resize(populationSize_);

            // fill remaining individuals with random individuals
            int numNeeded = populationSize_ - selection_->howMany();
            auto newIndividuals = RandomNumberGenerator::getInstance().lhs(numNeeded, optItems_.size(),
                                                                           optItems_.getLb(), optItems_.getUb(),
                                                                           logspace_);
            for (int j = 0; j < newIndividuals.size() - 1; j++) {
                (*population_)[selection_->howMany() + j] = Individual(newIndividuals[j]);
            }

            // individuals are destroyed at end of scope.
        }

        std::cout << "best individual: " << (*population_)[0][0] << ", " << (*population_)[0][1] << std::endl;
//        for (auto i: *population_) {
//            for (auto j : i) {
//                std::cout << j << "," << std::endl;
//            }
//            std::cout << std::endl;
//        }


    }

}