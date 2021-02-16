//
// Created by Ciaran on 12/02/2021.
//

#include "Mutation.h"

#include <utility>
#include "OptItems.h"

namespace opt {

    Mutation::Mutation(SharedPopulation population) :
            Operator(std::move(population)) {}

    Mutation::Mutation(SharedPopulation population, SharedPopulation nextGen) :
            Operator(std::move(population),
                     std::move(nextGen)) {}

    Mutation::Mutation(SharedPopulation population, SharedPopulation nextGen, OptItems *optItems)
            : Operator(std::move(population), std::move(nextGen)), optItems_(optItems_) {}

    OptItems *Mutation::getOptItems() const {
        return optItems_;
    }

    void Mutation::setOptItems(OptItems *optItems) {
        optItems_ = optItems;
    }


}