//
// Created by Ciaran on 06/02/2021.
//

#ifndef SRES_OPTIMIZER_H
#define SRES_OPTIMIZER_H

#include "OptItems.h"
#include "RandomNumberGenerator.h"

/*
 * Its useful to be able to provide our own objective functions
 * but it introduces overhead. It would be nice to be able
 * to pass back an instance of roadrunner though.
 *
 * Could be naughty and upload the static rr dist
 * to github for linking?
 */

namespace opt {

    using DoubleMatrix = std::vector<std::vector<double>>;
    using DoubleVector = std::vector<double>;

    /**
     * @brief cost function with signature for parameters (to estimate).
     * @param individual or genome. This is a double vector representing candiate parameters
     * @return Fitness of the input individual.
     */
    typedef double(*CostFunction)(double *);


    /**
     * @brief base class for optimization algorithms.
     *
     */
    class Optimizer {

    public:

        /**
         * @brief default construct optimizer
         */
        Optimizer() = default;

        /**
         * @brief virutal destructor
         */
        virtual ~Optimizer() = default;

        /**
         * @brief construct an Optimizer from components required to make
         * up the OptItems. The OptItems are build from @param startingValues
         * @param lb and @param ub on an index by index basis. Therefore,
         * they must all be of the same size.
         */
        Optimizer(
                CostFunction cost, const DoubleVector &startingValues,
                const DoubleVector &lb, const DoubleVector &ub, bool logspace,
                bool verbose
        );

        /**
         * @brief entrance method for running
         * of the algorithm. Subclasses must provide
         * their own implementation.
         * @details class level variables are modified
         * during optimization.
         * @returns true on success.
         */
        virtual void fit() = 0;

        /**
         * @brief construct an optimizer using the OptItems
         * container
         */
        Optimizer(CostFunction cost, OptItems optItems);

        /**
         * @brief getter for cost function
         */
        [[nodiscard]] CostFunction getCost() const;

        /**
         * @brief setter for cost function
         */
        void setCost(CostFunction cost);

        void setSeed(unsigned long long int seed);

        [[nodiscard]] double getBestFitnessValue() const;

        void setBestValue(double bestValue);

        [[nodiscard]] int getNumberOfParameters() const;

        void setNumberOfParameters(int numberOfParameters);

    protected:



        /**
         * @brief the parameters for the best solution
         */
        std::vector<double> solutionValues_;

        /**
        * @brief The fitness of the last evaluation.
        */
        double fitnessValue_ = 10000000.0;

        /**
         * @brief the fitness of the best evaluation so far
         */
        double bestFitnessValue_ = 10000000.0;

        /**
         * @brief optimization items. Defines the fitting start
         * values as well as lower and upper bounds. Also
         * has some methods to performs checks
         */
        OptItems optItems_;

        /**
         * @brief cost function. The input (double*) are parameter
         * values to try and the output are the fitness values of
         * those parameters.
         */
        CostFunction cost_; // way to inject cost function from Python

        /**
         * @brief how many parameters are in the estimation problem.
         * @details this information is available from the size of the
         * OptItems container which should be used instead.
         */
        int numberOfParameters_; // number of parameters to estimate

        /**
         * @brief output info during optimization
         */
        bool verbose_ = false;

        /**
         * @brief do optimization in logspace
         */
        bool logspace_ = true;

    };

}

#endif //SRES_OPTIMIZER_H
