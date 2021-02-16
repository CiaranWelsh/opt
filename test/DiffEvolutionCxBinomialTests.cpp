#include "gtest/gtest.h"

#include "DiffEvolutionCxBinomial.h"
#include "RandomNumberGenerator.h"

using namespace opt;

class DiffEvolutionCxBinomialTests : public ::testing::Test {
public:
    DiffEvolutionCxBinomialTests() = default;
};



/**
 * Not a good test of course, but better than nothing
 */
TEST_F(DiffEvolutionCxBinomialTests, test1) {
    // set seed
    RandomNumberGenerator::getInstance(5);
    Population pop({
                           {0.1,  0.4,  0.6},
                           {0.4,  0.4,  0.5},
                           {0.2,  0.6,  0.8},
                   });
    Population popMut({
                           {0.2,  0.6,  0.8},
                           {0.4,  0.4,  0.5},
                           {0.1,  0.4,  0.6},
                   });
    SharedPopulation sharedPopulation = std::make_shared<Population>(pop);
    SharedPopulation nextGen = std::make_shared<Population>(popMut);
    DiffEvolutionCxBinomial cx(sharedPopulation, nextGen, 0.15);
    cx.crossover();
    ASSERT_EQ(0.6, (*cx.getPopulation())[0][2]);
    ASSERT_EQ(0.6, (*cx.getNextGen())[0][2]);
}























