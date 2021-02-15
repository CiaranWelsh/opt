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
    std::vector<double> lowerBounds({2.8, 0.3});
    std::vector<double> upperBounds({3.2, 0.7});
    std::vector<double> startingVals({2, 5});

    // it'll automatically, use lhs. No other option.
    // population needs to create individuals

    // ElitistSelection
    TourneySelection tourneySelection(5, 25);
    CxOnePoint cxOnePoint;
    PointMutation pointMutation(0.3);

    GeneticAlgorithm geneticAlgorithm(
            BealeFunction, 100, 25, startingVals, lowerBounds, upperBounds,
            &tourneySelection, &pointMutation, &cxOnePoint
    );

    geneticAlgorithm.fit();
//
//    Individual bestIndividual = geneticAlgorithm.getBestIndividual();
//
//    std::unordered_map<int, double> hallOfFame = geneticAlgorithm.getHallOfFame();


}