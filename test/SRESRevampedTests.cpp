#include <cmath>
#include "gtest/gtest.h"
#include "SRESRevamped.h"

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


class SRESRevampedTests : public ::testing::Test {

public:
    SRESRevampedTests() = default;

};


TEST_F(SRESRevampedTests, TestConstruction) {
    SRESRevamped sres(BealeFunction, 10, 5,
              {8.324, 7.335},
              {0.01, 0.01}, {100, 100}, 7, 25, LOGSPACE, true,
              10, 3);
    sres.fit();

}
























