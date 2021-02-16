#include "gtest/gtest.h"
#include "CostFunctions.h"
#include "DiffEvolution.h"
#include "DiffEvolutionCxBinomial.h"
#include "DiffEvolutionMutation1.h"
#include "DiffEvolutionSelection.h"
using namespace opt;

class DiffEvolutionTests : public ::testing::Test {
public:
    DiffEvolutionTests() = default;
};


TEST_F(DiffEvolutionTests, test1) {
    std::vector<double> lowerBounds({0.1, 0.1});
    std::vector<double> upperBounds({10, 10});
    std::vector<double> startingVals({2, 5});

    DiffEvolutionMutation1 mut;
    mut.setF(1);
    DiffEvolutionCxBinomial cx;
    cx.setPb(0.75);
    DiffEvolutionSelection selection;

    DiffEvolution diffEvolution(
            BealeFunction, 15, 100, startingVals, lowerBounds, upperBounds,
            &selection, &mut, &cx
    );
    diffEvolution.fit();
}

// todo need to deal with boundary conditions





































