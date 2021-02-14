
#include "gtest/gtest.h"
#include "MockPopulationOptimizer.h"
#include "TourneySelection.h"

class TournamentSelectionTests : public ::testing::Test {
public:
    MockPopulationOptimizer mockPopulationOptimizer;

    TournamentSelectionTests() {};
};


TEST_F(TournamentSelectionTests, test){
    TourneySelection t();
}






















