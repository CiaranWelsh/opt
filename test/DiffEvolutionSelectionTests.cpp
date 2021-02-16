#include "gtest/gtest.h"

#include "DiffEvolutionMutation1.h"

using namespace opt;

class DiffEvolutionSelectionTests : public ::testing::Test {
public:
    DiffEvolutionSelectionTests() = default;
};



/**
 * Not a good test of course, but better than nothing
 */
TEST_F(DiffEvolutionSelectionTests, test1) {
    Population pop({
                           {0.1,  0.4,  0.6},
                           {0.4,  0.4,  0.5},
                           {0.2,  0.6,  0.8},
                           {0.5,  0.6,  0.8},
                           {0.7,  0.78, 0.48},
                           {0.9,  0.3,  0.89},
                           {0.32, 0.68, 0.08},
                           {0.42, 0.66, 0.988},
                   });
    SharedPopulation sharedPopulation = std::make_shared<Population>(pop);
    SharedPopulation nextGen = std::make_shared<Population>(pop);
    DiffEvolutionMutation1 mutation(sharedPopulation, nextGen, 1.2);
    mutation.mutate();
    ASSERT_EQ(0.1, (*mutation.getPopulation())[0][0]);
    ASSERT_NE(0.1, (*mutation.getNextGen())[0][0]);
}























