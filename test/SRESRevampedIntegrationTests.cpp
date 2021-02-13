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

using namespace opt;

class SRESRevampedIntegrationTests {
public:

    SRESRevampedIntegrationTests() = default;
};


/**
 * This is how I want to use the algorthm
 */
TEST_F(SRESRevampedIntegrationTests, test) {
    std::vector<double> lowerBounds;
    std::vector<double> upperBounds;
    std::vector<double> startingVals;

    // it'll automatically, use lhs. No other option.
    // population needs to create individuals

    // ElitistSelection
    TourneySelection tourneySelection;
    BasicMutation mutation;  // use this: http://liacs.leidenuniv.nl/~nijssensgr/CI/2012/9%20genetic%20algorithm.pdf
    IntermediateRecombination intermediateRecombination; // discrete and global recombination also exist

    GeneticAlgorithm geneticAlgorithm(
            15, lowerBounds, upperBounds, startingVals,
            &tourneySelection, &mutation, &intermediateRecombination
    );

    geneticAlgorithm.fit();

    Individual bestIndividual = geneticAlgorithm.getBestIndividual();

    std::unordered_map<int, double> hallOfFame = geneticAlgorithm.getHallOfFame();


}