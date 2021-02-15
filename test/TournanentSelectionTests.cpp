
#include "gtest/gtest.h"
//#include "MockPopulationOptimizer.h"
#include "TourneySelection.h"
#include "Population.h"
#include "RandomNumberGenerator.h"
#include "CostFunctions.h"

using namespace opt;

class TournamentSelectionTests : public ::testing::Test {
public:

    TournamentSelectionTests() = default;;
};


TEST_F(TournamentSelectionTests, test){
    RandomNumberGenerator rng = RandomNumberGenerator::getInstance(5); // set seed
    Population pop({
                           {3.01, 0.56},
                           {3.02, 0.55},
                           {3.03, 0.54},
                           {3.04, 0.53},
                           {3.05, 0.52},
                           {3.01, 0.51},
                           {3.07, 0.58},
                           {3.08, 0.59},
    });
    TourneySelection tourneySelection(std::make_shared<Population>(pop), 3, 10);
    auto selection = tourneySelection.select(<#initializer#>);
    ASSERT_EQ(std::vector( { 7, 7, 4, 2, 3, 4, 7, 2, 3, 5 }), selection);

}






















