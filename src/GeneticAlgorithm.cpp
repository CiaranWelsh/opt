//
// Created by Ciaran on 13/02/2021.
//

#include <iostream>
#include "GeneticAlgorithm.h"


namespace opt {

    GeneticAlgorithm::GeneticAlgorithm(
            CostFunction cost, int populationSize, int numGenerations, const DoubleVector& startingVals,
            const DoubleVector& lowerBounds, const DoubleVector& upperBounds,
            Selection *select, Mutation *mutate, CrossOver *crossOver,
            bool logspace, bool verbose,
            int numLHSInitSamples, int numGenForLHSInitSamples)
            : PopulationOptimizer(cost, populationSize, numGenerations, startingVals,
                                  lowerBounds, upperBounds, select,
                                  mutate, crossOver){
        Population pop = Population::fromLHS(populationSize_, optItems_.size(),optItems_.getLb(), optItems_.getUb(), logspace_ );
        population_ = std::make_shared<Population>(pop);
    }

    void GeneticAlgorithm::fit() {

            std::cout << (*population_)[0][0] << std::endl;

        selection_->setPopulation(population_);

        for (int i=0; i< numGenerations_; i++){
            population_->evaluate(cost_);
            selection_->select(nextGen_);

            crossover_->setPopulation(nextGen_);
            for (auto [i, j] = std::tuple(0, 1); j<nextGen_->size(); i++, j++){
                crossover_->crossover((*nextGen_)[i], (*nextGen_)[j]);
            }

            mutation_->setPopulation(nextGen_);
            mutation_->mutate();

            // fill remaining individuals with random
            int numNeeded = populationSize_ - selection_->getHowMany();
            auto newIndividuals = RandomNumberGenerator::getInstance().lhs(numNeeded, optItems_.size(), optItems_.getLb(), optItems_.getUb(), logspace_);
            for (int j=0; j<newIndividuals.size(); j++){
                (*nextGen_)[selection_->getHowMany() + j] = Individual(j);
            }
            population_ = nextGen_;
        }

        for (auto i: *population_){
            for (auto j : i){
                std::cout << j << "," << std::endl;
            }
            std::cout << std::endl;
        }


    }

}