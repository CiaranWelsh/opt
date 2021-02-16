//
// Created by Ciaran on 15/02/2021.
//

#ifndef OPT_DIFFEVOLUTION_H
#define OPT_DIFFEVOLUTION_H

#include "PopulationOptimizer.h"

namespace opt {

    class DiffEvolution : public PopulationOptimizer {

    public:
        // todo some refactoring needed here. Childrate is part of sres, not other population methods.
        //  The lhs stuff might be worth keeping in the long run.
        DiffEvolution(CostFunction cost, int populationSize, int numGenerations,
                const DoubleVector &startingValues, const DoubleVector &lb,
                const DoubleVector &ub, Selection *selection,
                Mutation *mutation, CrossOver *crossover, int childRate = 7, bool logspace = false,
                bool verbose = true, int numLHSInitSamples = 0, int numGenerationsForLHSInitSamples = 0);

        void fit() override;

    };
}


#endif //OPT_DIFFEVOLUTION_H
