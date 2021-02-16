//
// Created by Ciaran on 06/02/2021.
//

#include <iostream>
#include "PopulationOptimizer.h"
#include "Selection.h"
#include "CrossOver.h"
#include "Mutation.h"
#include <set>
#include <execution>

namespace opt {

    PopulationOptimizer::PopulationOptimizer(
            CostFunction cost, int populationSize, int numGenerations,
            const DoubleVector &startingValues, const DoubleVector &lb,
            const DoubleVector &ub, Selection *selection,
            Mutation *mutation, CrossOver *crossover, int childRate, bool logspace,
            bool verbose, int numLHSInitSamples, int numGenerationsForLHSInitSamples)
            : Optimizer(cost, startingValues, lb, ub, logspace, verbose),
              populationSize_(populationSize),
              numGenerations_(numGenerations),
              selection_(selection),
              mutation_(mutation),
              crossover_(crossover),
              childRate_(childRate),
              numLHSInitSamples_(numLHSInitSamples),
              numGenerationsForLHSInitSamples_(numGenerationsForLHSInitSamples){}


    int PopulationOptimizer::getPopulationSize() const {
        return populationSize_;
    }

    void PopulationOptimizer::setPopulationSize(int populationSize) {
        PopulationOptimizer::populationSize_ = populationSize;
    }

    int PopulationOptimizer::getChildRate() const {
        return childRate_;
    }

    void PopulationOptimizer::setChildRate(int childrate) {
        childRate_ = childrate;
    }

    int PopulationOptimizer::getNumGenerations() const {
        return numGenerations_;
    }

    void PopulationOptimizer::setNumGenerations(int numGenerations) {
        PopulationOptimizer::numGenerations_ = numGenerations;
    }

    double PopulationOptimizer::evaluate(Individual &individual) {
        double *pd = individual.data();
        return (*cost_)(pd);
    }


    int PopulationOptimizer::getCurrentGeneration() const {
        return currentGeneration_;
    }

    void PopulationOptimizer::setCurrentGeneration(int currentGeneration) {
        currentGeneration_ = currentGeneration;
    }


    SharedPopulation PopulationOptimizer::getPopulation() const {
        return population_;
    }

    void PopulationOptimizer::setPopulation(SharedPopulation sharedPopulation) {
        population_ = std::move(sharedPopulation);
    }

    const DoubleVector &PopulationOptimizer::getPopulationFitness() const {
        return populationFitness_;
    }

    void PopulationOptimizer::setPopulationFitness(const DoubleVector &populationFitness) {
        PopulationOptimizer::populationFitness_ = populationFitness;
    }

    DoubleMatrix PopulationOptimizer::findStartingSet() {
        RandomNumberGenerator rng = RandomNumberGenerator::getInstance();


        DoubleMatrix bestPop;
        double bestTrial = 100000000; // arbitrarily large to start with

        for (int trial = 0; trial < numLHSInitSamples_; trial++) {

            // initialize vector to store fitnesses
//            std::vector<double> fitnesses(populationSize_ * childRate_);

            // sample using lhs
//            DoubleMatrix trialPop = rng.lhs(
//                    populationSize_ * childRate_,
//                    numberOfParameters_,
//                    optItems_.getLb(),
//                    optItems_.getUb()
//            );

            // evolve a little
//            fit();


//            // evaluate the fitnesses using C++17's cool parallel for_each =]
//            double fitnessOfThisTrail = 0;
//            std::for_each(std::execution::par, trialPop.begin(), trialPop.end(),
//                          [this, &fitnessOfThisTrail](auto &ind) {
//                              double *pd = ind.data();
//                              fitnessOfThisTrail += (*cost_)(pd);
//                          });
//
//            if (fitnessOfThisTrail < bestTrial) {
//                // we've found a better starting set
//                bestTrial = fitnessOfThisTrail;
//                bestPop = trialPop;
//            }
        }
        return bestPop;
    }


}