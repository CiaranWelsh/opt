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
}






