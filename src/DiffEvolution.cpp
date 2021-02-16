//
// Created by Ciaran on 15/02/2021.
//

#include <iostream>
#include "DiffEvolution.h"


namespace opt {


    DiffEvolution::DiffEvolution(
            CostFunction cost, int populationSize, int numGenerations,
            const DoubleVector &startingValues, const DoubleVector &lb, const DoubleVector &ub,
            Selection *selection, Mutation *mutation, CrossOver *crossover, int childRate,
            bool logspace, bool verbose, int numLHSInitSamples,
            int numGenerationsForLHSInitSamples)
            : PopulationOptimizer(cost, populationSize,
                                  numGenerations,
                                  startingValues, lb, ub,
                                  selection, mutation,
                                  crossover, childRate,
                                  logspace, verbose,
                                  numLHSInitSamples,
                                  numGenerationsForLHSInitSamples) {}

    void DiffEvolution::fit() {
        Population pop(Population::fromLHS(
                populationSize_, numberOfParameters_, optItems_.getStartingValues(), optItems_.getLb(),
                optItems_.getUb(), logspace_)
        );
        population_ = std::make_shared<Population>(pop);

        // initialize next gen as copy of population
        nextGen_ = std::make_shared<Population>(pop);

        // initialize our operators with the populations
        selection_->setPopulation(population_);
        selection_->setNextGen(nextGen_);
        mutation_->setPopulation(population_);
        mutation_->setNextGen(nextGen_);
        crossover_->setPopulation(population_);
        crossover_->setNextGen(nextGen_);

        mutation_->setOptItems(&optItems_);

        // set best individual to any old solution to begin with
        bestIndividual = (*population_)[0];


        for (int gen = 0; gen < numGenerations_; gen++) {
            std::cout << "Current gen: " << gen << "; best fitness: " << bestFitnessValue_
                      << "\t\t; x: " << bestIndividual[0] << "\t\t; y: " << bestIndividual[1] << std::endl;

            mutation_->mutate();
            crossover_->crossover();

            // evaluate both populations. Evaluation needs
            // to be done before selection, which depends on
            // the fitnesses
            population_->evaluate(cost_);
            nextGen_->evaluate(cost_);

            // update our best solution so far
            Individual generationBest = *std::min_element(nextGen_->begin(), nextGen_->end());
            if (generationBest < bestIndividual) {
                bestIndividual = generationBest;
                bestFitnessValue_ = generationBest.getFitness();
                hallOfFame_[gen] = generationBest;
            }

            // do selection
            selection_->select();
        }
    };
}
