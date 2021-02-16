//
// Created by Ciaran on 12/02/2021.
//

#include "Selection.h"

namespace opt {

    Selection::Selection(SharedPopulation population, int howMany)
            : Operator(std::move(population)), howMany_(howMany) {}

    Selection::Selection(int howMany, int numEstimatedParameters)
            : howMany_(howMany){}

    int Selection::howMany() const {
        return howMany_;
    }

    void Selection::setHowMany(int howMany) {
        howMany_ = howMany;
    }

}