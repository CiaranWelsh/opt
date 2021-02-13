//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRESRevamped_SRESRevampedREVAMPED_H
#define SRESRevamped_SRESRevampedREVAMPED_H


#include <vector>
#include <random>
#include <functional>
#include "OptItems.h"
#include "PopulationOptimizer.h"

namespace opt {
    
    class SRESRevamped : public PopulationOptimizer {

    public:

        SRESRevamped() = default;

        SRESRevamped(CostFunction cost, int populationSize, int numGenerations,
             const DoubleVector &startingValues, const DoubleVector &lb,
             const DoubleVector &ub, int childrate,
             int stopAfterStalledGenerations = 0, bool logspace = false,
             bool verbose = false,
             int numLHSInitSamples = 0,
             int numGenerationsForLHSInitSamples = 5);

        bool fit() override;

    private:
        int findBestIndividual() override;

        bool initialize() override;

        bool mutate() override;

        void select() override;

        bool replicate() override;

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


#endif //SRESRevamped_SRESRevampedREVAMPED_H
