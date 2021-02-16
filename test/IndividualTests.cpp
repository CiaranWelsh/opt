//
// Created by Ciaran on 13/02/2021.
//

#include "gtest/gtest.h"

#include "Individual.h"
#include "CostFunctions.h"

using namespace opt;

class IndividualTests : public ::testing::Test {

public:

    IndividualTests() = default;

};


TEST_F(IndividualTests, TestValuesEqual) {
    std::vector<double> v({15, 7, 2, 5});
    Individual individual(v);
    ASSERT_EQ(v, individual.getValues());
}

TEST_F(IndividualTests, TestSlice) {
    Individual container({0, 1, 2, 3, 4, 5, 6});
    Individual expected({0});
    Individual actual = container(0, 1);
    ASSERT_EQ(expected, actual);
}


TEST_F(IndividualTests, TestCostFunctionEvaluation) {
    Individual individual({3.01, 0.501});
    double fitness = individual.evaluate(BealeFunction);
    ASSERT_NEAR(0.01, fitness, 0.01);
}


TEST_F(IndividualTests, TestVectorAddition) {
    Individual i1({1, 2, 3});
    Individual i2({4, 5, 6});
    Individual i3 = i1 + i2;
    Individual expected({5, 7, 9});
    ASSERT_EQ(expected, i3);
}


TEST_F(IndividualTests, TestVectorSubtraction) {
    Individual i1({1, 2, 3});
    Individual i2({4, 5, 6});
    Individual i3 = i2 - i1;
    Individual expected({3, 3, 3});
    ASSERT_EQ(expected, i3);
}

TEST_F(IndividualTests, TestVectorMultiplication) {
    Individual i1({1, 2, 3});
    Individual i2({4, 5, 6});
    Individual i3 = i2 * i1;
    Individual expected({4, 10, 18});
    ASSERT_EQ(expected, i3);
}

TEST_F(IndividualTests, TestVectorDivision) {
    Individual i1({3, 4, 6});
    Individual i2({6, 12, 18});
    Individual i3 = i2 / i1;
    Individual expected({2, 3, 3});
    ASSERT_EQ(expected, i3);
}


TEST_F(IndividualTests, TestVectorAdditionWithScalar) {
    Individual i1({1, 2, 3});
    double x = 2;
    Individual i3 = i1 + x;
    Individual expected({3, 4, 5});
    ASSERT_EQ(expected, i3);
}


TEST_F(IndividualTests, TestVectorSubtractionWithScalar) {
    Individual i1({1, 2, 3});
    double x = 2;
    Individual i3 = i1 - x;
    Individual expected({-1, 0, 1});
    ASSERT_EQ(expected, i3);
}

TEST_F(IndividualTests, TestVectorMultiplicationWithScalar) {
    Individual i1({1, 2, 3});
    double x = 2;
    Individual i3 = i1 * x;
    Individual expected({2, 4, 6});
    ASSERT_EQ(expected, i3);
}

TEST_F(IndividualTests, TestVectorDivisionWithScalar) {
    Individual i1({3, 4, 6});
    double x = 2;
    Individual i3 = i1 / x;
    Individual expected({1.5, 2, 3});
    ASSERT_EQ(expected, i3);
}










