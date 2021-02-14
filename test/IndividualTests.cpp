//
// Created by Ciaran on 13/02/2021.
//

#include "gtest/gtest.h"

#include "Individual.h"

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

TEST_F(IndividualTests, TestSlice){
    Individual container({0, 1, 2, 3, 4, 5, 6});
    Individual expected({0});
    Individual actual = container(0, 1);
    ASSERT_EQ(expected, actual);
}













