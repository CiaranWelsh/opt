//
// Created by Ciaran on 12/02/2021.
//

#include "SRESRevamped.h"


namespace opt {
    SRESRevamped::SRESRevamped(CostFunction cost, int populationSize,
                               int numGenerations, const DoubleVector &startingValues, const DoubleVector &lb,
                               const DoubleVector &ub, int childrate, int stopAfterStalledGenerations, bool logspace,
                               bool verbose,
                               int numLHSInitSamples, int numGenerationsForLHSInitSamples)
            : PopulationOptimizer(
            cost, populationSize, numGenerations,
            startingValues, lb, ub, childrate,
            stopAfterStalledGenerations, logspace, verbose,
            numLHSInitSamples, numGenerationsForLHSInitSamples) {};




}