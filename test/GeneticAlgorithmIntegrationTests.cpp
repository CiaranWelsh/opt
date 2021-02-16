//
// Created by Ciaran on 13/02/2021.
//

#include "gtest/gtest.h"
#include "Population.h"
#include "Individual.h"
#include "Selection.h"
#include "Mutation.h"
#include "CrossOver.h"
#include "GeneticAlgorithm.h"
#include "TourneySelection.h"
#include "PointMutation.h"
#include "CxOnePoint.h"
#include "CostFunctions.h"

using namespace opt;

class GeneticAlgorithmIntegrationTests : public ::testing::Test {
public:

    GeneticAlgorithmIntegrationTests() = default;
};


/**
 * This is how I want to use the algorthm
 */
TEST_F(GeneticAlgorithmIntegrationTests, iun) {
    std::vector<double> lowerBounds({0.1, 0.1});
    std::vector<double> upperBounds({10, 10});
    std::vector<double> startingVals({2, 5});

    // it'll automatically, use lhs. No other option.
    // population needs to create individuals

    // ElitistSelection
    TourneySelection tourneySelection(3, 3, 2);
    CxOnePoint cxOnePoint;
    PointMutation pointMutation(0.1);

    GeneticAlgorithm geneticAlgorithm(
            BealeFunction, 10, 20, startingVals, lowerBounds, upperBounds,
            &tourneySelection, &pointMutation, &cxOnePoint
    );

    geneticAlgorithm.fit();
//
//    Individual bestIndividual = geneticAlgorithm.getBestIndividual();
//
//    std::unordered_map<int, double> hallOfFame = geneticAlgorithm.getHallOfFame();


}




/**
 * How can I compare the efficiency of these different algorithms?
 * Change the stopping criteria to tolerance error of true solution.
 * Compare the number of generations required to find the solution.
 *
 * Could also compare the algorithm against the pure random search.
 */
















