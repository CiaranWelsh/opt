
#include "gtest/gtest.h"
//#include "MockPopulationOptimizer.h"
#include "PointMutation.h"
#include "Population.h"
#include "RandomNumberGenerator.h"
#include "CostFunctions.h"

using namespace opt;

class PointMutationTests : public ::testing::Test {
public:

    PointMutationTests() = default;;
};


TEST_F(PointMutationTests, test) {
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
    PointMutation pointMutation(std::make_shared<Population>(pop));
    pointMutation.mutate();
    Population expected({
                                {3.01,    0.867908},
                                {3.02,    0.55},
                                {3.03,    0.54},
                                {7.18652, 0.53},
                                {3.05,    0.52},
                                {3.01,    1.62347},
                                {3.07,    0.58},
                                {9.44631, 0.59},
                        });

    for (auto i: *pointMutation.getPopulation()) {
        for (auto j: i) {
            std::cout << j << ",";
        }
        std::cout << std::endl;
    }

    ASSERT_EQ(0.867908, expected[0][1]);

}






















