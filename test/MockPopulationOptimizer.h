//
// Created by Ciaran on 14/02/2021.
//

#ifndef OPT_MOCKPOPULATIONALGORITHM_H
#define OPT_MOCKPOPULATIONALGORITHM_H

#include "gmock/gmock.h"
#include "PopulationOptimizer.h"

using namespace opt;

class MockPopulationOptimizer : public PopulationOptimizer{
    MOCK_METHOD(void, fit, (), (override));
};


#endif //OPT_MOCKPOPULATIONALGORITHM_H
