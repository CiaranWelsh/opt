
#include "gtest/gtest.h"
#include "Container.h"
#include <algorithm>
#include <chrono>
#include <execution>
/**
 * Population is an Individual container.
 * An individual is more or less just a double vector.
 */

using namespace opt;


class ContainerTests : public ::testing::Test {

public:

    ContainerTests() = default;

};

TEST_F(ContainerTests, TestSlice){
    Container<int> container({0, 1, 2, 3, 4, 5, 6});
    Container<int> expected({2, 3, 4});
    Container<int> actual = container.slice(2, 5);
    ASSERT_EQ(expected, actual);
}
TEST_F(ContainerTests, TestSliceWith0And1){
    Container<int> container({0, 1, 2, 3, 4, 5, 6});
    Container<int> expected({0});
    Container<int> actual = container.slice(0, 1);
    ASSERT_EQ(expected, actual);
}