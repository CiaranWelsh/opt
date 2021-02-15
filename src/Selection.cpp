//
// Created by Ciaran on 12/02/2021.
//

#include "Selection.h"

namespace opt {

    Selection::Selection(SharedPopulation population, int howMany)
            : Operator(std::move(population)), howMany_(howMany),
              nextGen_(std::make_shared<Population>(howMany_, (*population_)[0].size())) {}

    Selection::Selection(int howMany, int numEstimatedParameters)
            : howMany_(howMany),
              nextGen_(std::make_shared<Population>(howMany_, numEstimatedParameters)) {}

    int Selection::howMany() const {
        return howMany_;
    }

    void Selection::setHowMany(int howMany) {
        howMany_ = howMany;
    }


    const SharedPopulation &Selection::getNextGen() const {
        return nextGen_;
    }

    void Selection::setNextGen(const SharedPopulation &nextGen) {
        nextGen_ = nextGen;
    }
}