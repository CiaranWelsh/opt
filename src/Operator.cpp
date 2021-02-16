//
// Created by Ciaran on 13/02/2021.
//

#include "Operator.h"

#include <utility>

namespace opt {

    Operator::Operator(SharedPopulation population)
        : population_(std::move(population)){}

    const SharedPopulation &Operator::getPopulation() const {
        return population_;
    }

    void Operator::setPopulation(const SharedPopulation &population) {
        population_ = population;
    }

    const SharedPopulation &Operator::getNextGen() const {
        return nextGen_;
    }

    void Operator::setNextGen(const SharedPopulation &nextGen) {
        nextGen_ = nextGen;
    }

    Operator::Operator(SharedPopulation population, SharedPopulation nextGen)
        : population_(std::move(population)), nextGen_(std::move(nextGen)){}
}






