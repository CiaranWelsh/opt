#include <cmath>
#include "gtest/gtest.h"
#include "SRES.h"

#define LOGSPACE false

using namespace opt;

int N = 10;


/**
 * minimum = f(3, 0.5) = 0
 */
double BealeFunction(double *input_params) {
#ifdef LOGSPACE
    double x = pow(10, input_params[0]);
    double y = pow(10, input_params[1]);
#else
    double x = input_params[0];
    double y = input_params[1];
#endif
    double first = pow(1.5 - x + x * y, 2);
    double second = pow(2.25 - x + x * pow(y, 2), 2);
    double third = pow(2.625 - x + x * pow(y, 3), 2);
    return first + second + third;
};

double ThreeHumpCamel(double *input_params) {
    // global minimum at 0, 0
#ifdef LOGSPACE
    double x = pow(10, input_params[0]);
    double y = pow(10, input_params[1]);
#else
    double x = input_params[0];
    double y = input_params[1];
#endif
    return 2 * (x * x) - 1.05 * (x * x * x * x) + ((x * x * x * x * x * x) / 6) + x * y + y * y;
}


class SRESTests : public ::testing::Test{

public:
    SRESTests() = default;

};

TEST_F(SRESTests, TestFindStartingSetBeale) {

    SRES sres(BealeFunction, 10, 5,
              {8.324, 7.335},
              {0.01, 0.01}, {100, 100}, 7, 25, LOGSPACE, true,
              10, 3);

    sres.findStartingSet();
}


TEST_F(SRESTests, TestFindBestIndividual) {
    SRES sres(BealeFunction, 300, 250,
              {8.324, 7.335},
              {0.01, 0.01}, {100, 100}, 7, 25, LOGSPACE, true,
              10, 3);
//    sres.setSeed(4);
    sres.fit();
//    DoubleMatrix pop = sres.getPopulation();

//    size_t idx = sres.findBestIndividual();
//
//
//    sres;
}


TEST_F(SRESTests, Fit) {
//    CostFunction cost = GetParam();
    SRES sres(BealeFunction, 50, 50,
              {8.324, 7.335},
              {0.001, 0.001}, {5, 5}, 7, 25, LOGSPACE, true);
    sres.fit();
    auto sol = sres.getSolutionValues();

    for (auto i: sol) {
        std::cout << i << std::endl;
    }
//    ASSERT_NEAR(3.0, sol[0], 0.01);
//    ASSERT_NEAR(0.5, sol[1], 0.01);
//    ASSERT_TRUE(false);
}


//INSTANTIATE_TEST_SUITE_P(ParameterisedTestTest, SRESTests, ::testing::Values(BealeFunction, ThreeHumpCamel));








































