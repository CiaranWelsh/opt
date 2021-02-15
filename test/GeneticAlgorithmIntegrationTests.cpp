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
    std::vector<double> lowerBounds;
    std::vector<double> upperBounds;
    std::vector<double> startingVals;

    // it'll automatically, use lhs. No other option.
    // population needs to create individuals

    // ElitistSelection
    TourneySelection tourneySelection(5, 25);
    CxOnePoint cxOnePoint;
    PointMutation pointMutation(0.3);

    GeneticAlgorithm geneticAlgorithm(
            BealeFunction, 100, 25, lowerBounds, upperBounds, startingVals,
            &tourneySelection, &pointMutation, &cxOnePoint
    );

    geneticAlgorithm.fit();
//
//    Individual bestIndividual = geneticAlgorithm.getBestIndividual();
//
//    std::unordered_map<int, double> hallOfFame = geneticAlgorithm.getHallOfFame();


}