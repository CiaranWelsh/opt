//
// Created by Ciaran on 15/02/2021.
//

#include "DiffEvolutionMutation1.h"

#include <utility>
#include "RandomNumberGenerator.h"

namespace opt {

    DiffEvolutionMutation1::DiffEvolutionMutation1(SharedPopulation population, SharedPopulation nextGen, double F)
            : Mutation(std::move(population), std::move(nextGen)), F_(F) {}


    void DiffEvolutionMutation1::mutate() {
        //randomly choose r1, r2 and r3, to be indices in the population.
        // They should not be equal.
        for (int i = 0; i < population_->size(); i++) {
            RandomNumberGenerator rng = RandomNumberGenerator::getInstance();
            std::vector<int> r = rng.uniformIntWithoutReplacement(0, population_->size(), 3);
            Individual &xr1 = (*population_)[r[0]];
            Individual &xr2 = (*population_)[r[1]];
            Individual &xr3 = (*population_)[r[2]];
            (*nextGen_)[i] = xr1 +  ((xr2-xr3) * F_);
        }

    }

    double DiffEvolutionMutation1::getF() const {
        return F_;
    }

    void DiffEvolutionMutation1::setF(double f) {
        F_ = f;
    }

}
