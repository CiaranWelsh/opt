//
// Created by Ciaran on 13/02/2021.
//

#include "gtest/gtest.h"

#include "Population.h"
#include "Individual.h"
#include <algorithm>
#include <chrono>
#include <execution>
#include "CostFunctions.h"
#include "RandomNumberGenerator.h"

/**
 * Population is an Individual container.
 * An individual is more or less just a double vector.
 */

using namespace opt;


class PopulationTests : public ::testing::Test {

public:

    PopulationTests() = default;

};


TEST_F(PopulationTests, TestInstantiateFromInitLists) {
    ASSERT_NO_THROW(
            Population population({
                                          {1, 2, 3},
                                          {4, 5, 6},
                                          {7, 8, 9},
                                  });
    );
}

TEST_F(PopulationTests, TestInstantiateFromInts) {
    Population population(10, 3);
    population[0] = Individual({1, 2, 3});
    ASSERT_EQ(population[0][2], 3);
    ASSERT_EQ(population.size(), 10);
    ASSERT_EQ(population[0].size(), 3);
}


TEST_F(PopulationTests, CheckThatWeCanSortPopulation) {
    Population population({
                                  {1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 9},
                          });
    population[0].setFitness(30);
    population[1].setFitness(20);
    population[2].setFitness(10);

    // order should be 10, 20 30

    std::vector<std::vector<double>> expected({
                                                      {7, 8, 9},
                                                      {4, 5, 6},
                                                      {1, 2, 3},
                                              });
    std::sort(std::execution::par, population.begin(), population.end(), [](const Individual &a, const Individual &b) {
        return a > b;
    });
    ASSERT_EQ(1.0, population[0][0]);


}

/**
 * Made constructing Population use multithreading.
 * With 1 thread: it takes: 4772 microseconds
 * with 11 takes 1990. Noice.
 *
 */
TEST_F(PopulationTests, CreateAPopulationUsingLHS) {
    auto start = std::chrono::steady_clock::now();

    Population population = Population::fromLHS(10, 3, {0.01, 0.01, 0.01}, {10, 10, 10}, true);

    auto end = std::chrono::steady_clock::now();
    std::cout << "computation took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << std::endl;
    ASSERT_EQ(10, population.size());
    ASSERT_EQ(3, population[0].size());


}


TEST_F(PopulationTests, TestCostFunctionEvaluationWhenPopsizeLTNumThreads) {
    auto start = std::chrono::steady_clock::now();

    Population population({
                                  {3.5,  1.0},
                                  {2.5,  0.1},
                                  {3.25, 0.25},
                          });

    double fitness = population.evaluate(BealeFunction);

    auto end = std::chrono::steady_clock::now();
    std::cout << "fitness: " << fitness << std::endl;
    std::cout << "computation took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseonds" << std::endl;
    ASSERT_NEAR(13.2693, fitness, 0.1);

}

TEST_F(PopulationTests, TestCostFunctionEvaluationWhenPopsizeGTNumThreadsNoRemainder) {
    auto start = std::chrono::steady_clock::now();

    RandomNumberGenerator rng = RandomNumberGenerator::getInstance(10);
    Population population = Population::fromLHS(22, 2, {2.9, 0.4}, {3.1, 0.6}, false);
    double fitness = population.evaluate(BealeFunction);

    auto end = std::chrono::steady_clock::now();
    std::cout << "fitness: " << fitness << std::endl;
    std::cout << "computation took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseonds" << std::endl;
    ASSERT_NEAR(27.19477161939496, fitness, 0.1);

}

TEST_F(PopulationTests, TestCostFunctionEvaluationWhenPopsizeGTNumThreadsWithRemainder) {
    auto start = std::chrono::steady_clock::now();

    RandomNumberGenerator rng = RandomNumberGenerator::getInstance(10);

    Population population = Population::fromLHS(50000, 2, {2.9, 0.4}, {3.1, 0.6}, false);
    ASSERT_NEAR(population[0][0], 3.00675, 0.1); // makes sure our seed words

    double fitness = population.evaluate(BealeFunction);


    auto end = std::chrono::steady_clock::now();
    std::cout << "fitness: " << fitness << std::endl;
    std::cout << "computation took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseonds" << std::endl;

    double expected = 2.6364696533534953; //for seed = 10
    ASSERT_NEAR(expected, fitness, 0.1);

    /**
     * Notes: fitness: 2.63647
     * computation took: 2910 microseonds in serial (1 thread)
     *
     *
     */
}


TEST_F(PopulationTests, TestIndividualFitnessesUpdatedAfterEvaluation) {
    RandomNumberGenerator rng = RandomNumberGenerator::getInstance(10);

    Population population = Population::fromLHS(50000, 2, {2.9, 0.4}, {3.1, 0.6}, false);
    ASSERT_NEAR(population[0][0], 3.00675, 0.1); // makes sure our seed words

    population.evaluate(BealeFunction);

    ASSERT_NEAR(population.getIndividualFitnesses()[0], 0.0494881, 0.1);
}









