//
// Created by Ciaran on 13/02/2021.
//

#include "gtest/gtest.h"

#include "Population.h"
#include "Individual.h"
#include <algorithm>
#include <chrono>
#include <execution>
/**
 * Population is an Individual container.
 * An individual is more or less just a double vector.
 */

using namespace opt;


class PopulationTests : public ::testing::Test {

public:

    PopulationTests() = default;

};


TEST_F(PopulationTests, test) {
    Population population({
                                  {1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 9},
                          });

//    ASSERT_EQ(std::vector<double>({1, 2, 3}), population[0]);


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














