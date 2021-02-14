//
// Created by Ciaran on 06/02/2021.
//

#ifndef SRES_POPULATIONOPTIMIZER_H
#define SRES_POPULATIONOPTIMIZER_H

#include "Optimizer.h"
#include "Population.h"
#include "Selection.h"
#include "Mutation.h"
#include "CrossOver.h"
#include "unordered_map"

namespace opt {

    class PopulationOptimizer : public Optimizer {

    public:

        /**
         * @brief default constructor for EvolutionaryOptimizer
         */
        PopulationOptimizer() = default;

        /**
         * @brief default destructor for EvolutionaryOptimizer
         */
        ~PopulationOptimizer() override = default;

        /**
         * @brief Construct an EvolutionaryOptimizer from
         * @param cost a function to minimize. @see CostFunction
         * @param populationSize The size of parent population.
         * @param numGenerations The number of generations to run
         * @param startingValues Parameter starting values.
         * @param lb lower boundary for each parameter during optimization
         * @param ub upper boundary for each parameter during optimization
         * @param childRate Number of times to multiply populationSize by to get the number of children per generation
         * defaults to 7.
         * @param stopAfterStalledGenerations stop evolution after this many generations if fitness does not change.
         * @param logspace perform the optimization in logspace
         * @param verbose output logging information to console when a new best parameter set is found
         * @param numLHSInitSamples use latin hypercube random sampling this many times for
         * @param numGenerationsForLHSInitSamples generations each. Take the best of those runs for initial population.
         */
        PopulationOptimizer(
                CostFunction cost,
                int populationSize,
                int numGenerations,
                const DoubleVector &startingValues,
                const DoubleVector &lb,
                const DoubleVector &ub,
                Selection* selection,
                Mutation* mutation,
                CrossOver* crossOver,
                int childRate = 7,
                bool logspace = false,
                bool verbose = false,
                int numLHSInitSamples = 0,
                int numGenerationsForLHSInitSamples = 5
        );

        /**
         * @brief entry method for optimizer. Subclasses implement their
         * evolutionary strategy here. Users call the fit method to optimize
         * their parameters
         */
        void fit() override = 0;


        /**
         * @brief Evaluate the cost function with individual
         */
        double evaluate(Individual &individual);


        /**
         * @brief produce random populations using latin hypercube sampling
         *
         */
        virtual DoubleMatrix findStartingSet();

        /**
         * @brief getter for population size
         */
        [[nodiscard]] int getPopulationSize() const;

        /**
         * @brief setter for population size
         */
        void setPopulationSize(int populationSize);

        /**
         * @brief getter for child rate
         */
        [[nodiscard]] int getChildRate() const;

        /**
         * @brief setter for child rate
         */
        void setChildRate(int childrate);

        /**
         * @brief getter for number of generations
         */
        [[nodiscard]] int getNumGenerations() const;

        /**
         * @brief setter for number of generations
         */
        void setNumGenerations(int numGenerations);

        /**
         * @brief getter for current generation
         */
        [[nodiscard]] int getCurrentGeneration() const;

        /**
         * @brief setter for current generation
         */
        void setCurrentGeneration(int currentGeneration);

        /**
         * @brief getter for individuals matrix
         */
        [[nodiscard]] SharedPopulation getPopulation() const;

        /**
         * @brief setter for individuals matrix
         */
        void setPopulation(SharedPopulation population);

        /**
         * @brief getter for population fitness
         */
        [[nodiscard]] const DoubleVector &getPopulationFitness() const;

        /**
         * @brief setter for population fitness
         */
        void setPopulationFitness(const DoubleVector &populationFitness);

    protected:


        /**
         * @brief Selection operator
         */
        Selection* selection_;

        /**
         * @brief mutation operator
         */
        Mutation* mutation_;

        /**
         * @brief Selection operator
         */
        CrossOver* crossover_;

        /**
         * @brief counter for number of generations.
         */
        int currentGeneration_ = 0;


        /**
         * @brief the number of individuals in the parent population.
         * @details gets multiplied by childrate for
         * the child population size.
         */
        int populationSize_ = 100;

        /**
         * @brief the number of generations.
         * This is the stopping criteria for SRES.
         */
        int numGenerations_ = 500;

        /**
         * @brief matrix on individuals where rows are parameter
         * sets while columns are parameter candidates. In
         * other words, each row in this matrix is a candidate
         * solution.
         */
        SharedPopulation population_;

        /**
         * @brief A vector containing all the fitness
         * for each row of the individuals_ matrix.
         */
        DoubleVector populationFitness_;

        /**
         * @brief the number of times to multiply
         * the populationSize by for the number of
         * individuals in the child population.
         */
        int childRate_ = 7;

        /**
         * @brief the number of times to sample
         * initial population using latin hypercube sampling (LHS)
         * before feeding the best into the main algorithm. Default is 0,
         * meaning only a single population is sampled before executing the
         * main algorithm.
         */
        int numLHSInitSamples_ = 0;

        /**
         * @brief When sampling initial population using latin hypercube sampling
         * this number is used for the number of generations to run per sample parameter set. The default
         * is 0, meaning the parameter sets are samples only and are not optimized at all. It can be
         * beneficial to set this to some low number
         */
        int numGenerationsForLHSInitSamples_ = 0;

        /**
         * Collect the best values over generations. This is a map
         * with generation as key and fitness as value
         */
        std::unordered_map<int, double> hallOfFame_;

    };

}

#endif //SRES_POPULATIONOPTIMIZER_H
