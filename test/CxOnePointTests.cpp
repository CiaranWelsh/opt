#include "gtest/gtest.h"

#include "Individual.h"
#include "CxOnePoint.h"
#include "RandomNumberGenerator.h"
using namespace opt;


class CxOnePointTests : public ::testing::Test {

public:

    CxOnePointTests() = default;

};


TEST_F(CxOnePointTests, test) {

    Individual one ({1, 2, 3, 4, 5, 6});
    Individual two ({7, 8, 9, 10, 11, 12});

    CxOnePoint cxOnePoint;
    cxOnePoint.crossover(one, two);

    int x;

}