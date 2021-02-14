//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_POPULATION_H
#define SRES_POPULATION_H

#include <vector>
#include "Individual.h"
#include <memory>

namespace opt {

    class Population : public Container<Individual> {
    public:
        using Container<Individual>::Container;

        explicit Population(const std::vector<std::vector<double>>& input);

        Population(std::initializer_list<std::initializer_list<double>> input);

        /**
         * @brief preallocation constructor
         */
        Population(int npop, int nparam);

        /**
         * @brief create a random population using latin hypercube sampling
         * @param npop population size (how many rows)
         * @param nparam number of parameters to estimate (columns)
         * @param lb lower boundary for drawing samples. Of size nparam
         * @param ub upper boundary for drawing samples. Of size nparam
         * @param logspace Draw samples in log10 space
         */
        static Population fromLHS(
                int npop, int nparam, std::vector<double> lb, std::vector<double> ub, bool logspace);

        /**
         * @brief create a random population using latin hypercube sampling
         * @param npop population size (how many rows)
         * @param nparam number of parameters to estimate (columns)
         * @param startingParam User defined starting parameters, becomes individual
         * at index 0 of population
         * @param lb lower boundary for drawing samples. Of size nparam
         * @param ub upper boundary for drawing samples. Of size nparam
         * @param logspace Draw samples in log10 space
         */
        static Population fromLHS(
                int npop, int nparam, const std::vector<double> &startingParam, std::vector<double> lb,
                std::vector<double> ub,
                bool logspace);

        /**
         * @brief Determine the fitness of each individual in the
         * population.Does this using multithreading.
         */
        double evaluateMultiThreadedManual(CostFunction cost);

        double evaluate(CostFunction cost);


    private:
        /**
         * @brief fitness of the population.
         * Sum of the individuals
         */
        double populationFitness_ = std::numeric_limits<double>::max();

        /**
         * @brief ordered vector containing the calculated fitnesses
         * for each individual in the population.
         */
        std::vector<double> individualFitnesses_;
    };


    using SharedPopulation = std::shared_ptr<Population>;
}

#endif //SRES_POPULATION_H
