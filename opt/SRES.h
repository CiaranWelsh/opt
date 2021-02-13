//
// Created by Ciaran on 05/02/2021.
//

#ifndef SRES_SRES_H
#define SRES_SRES_H


#include <vector>
#include <random>
#include <functional>
#include "OptItems.h"
#include "PopulationOptimizer.h"

namespace opt {

    class SRES : public PopulationOptimizer {

    public:

        SRES() = default;

        SRES(CostFunction cost, int populationSize, int numGenerations,
             const DoubleVector &startingValues, const DoubleVector &lb,
             const DoubleVector &ub, int childrate,
             int stopAfterStalledGenerations = 0, bool logspace = false,
             bool verbose = false,
             int numLHSInitSamples = 0,
             int numGenerationsForLHSInitSamples = 5);

        [[nodiscard]] const DoubleVector &getMaxVariance() const;

        void setMaxVariance(const DoubleVector &maxVariance);

        [[nodiscard]] double getPf() const;

        void setPf(double pf);

        bool fit() override;


        void printCurrent();

        bool swap(size_t from, size_t to);

        bool replicate() override;
        bool replicate2();

        bool mutate() override;

        double phi(size_t indivNum);

        bool initialize() override;

        bool creation();

        /**
         * @brief locates the best individual of the current population
         * @details in doing so the solutionValues_ containing the
         * parameters belonging to the fittest individual are updated.
         *
         */
        int findBestIndividual() override;

        void select() override;

    private:
        /**
         * @brief variance of every position in the
         * populationi matrix
         * @note (probably correct, might not be)
         */
        DoubleMatrix variance_;

        /**
         * @brief largest variance for a particular population.
         * @note (maybe, is this the row/column oc variance_? todo look into what this is)
         */
        DoubleVector maxVariance_;

        /**
         * @brief parameter used in stochastic sorting.
         * @details usually has a value of 0.475
         */
        double pf_ = 0.475;

        double tau_ = 100.0;    // parameter for updating variances

        double tauPrime_ = 100.0;    // parameter for updating variances

        DoubleVector phi_; // should this actually be int vector?
    };

}
#endif //SRES_SRES_H
