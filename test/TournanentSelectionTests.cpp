
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


TEST_F(TournamentSelectionTests, MakeSureNextGenIsInstantiated){
    RandomNumberGenerator rng = RandomNumberGenerator::getInstance(5); // set seed
    Population pop({
                           {3.01, 0.56},
                           {3.02, 0.55},
                           {3.03, 0.54},
                           {3.04, 0.53},
    });
    pop[0].setFitness(12);
    pop[1].setFitness(3);
    pop[2].setFitness(8);
    pop[3].setFitness(6);

    TourneySelection tourneySelection(std::make_shared<Population>(pop), 2, 2);
    tourneySelection.select();
    ASSERT_EQ(3, (*tourneySelection.getPopulation())[0].getFitness());
    ASSERT_EQ(6, (*tourneySelection.getPopulation())[1].getFitness());

}






















