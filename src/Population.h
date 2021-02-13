//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_POPULATION_H
#define SRES_POPULATION_H

#include <vector>
#include "Individual.h"
#include <memory>

namespace opt {

    class Population: std::vector<Individual> {
    public:
        using std::vector<Individual>::vector;

    };

    using SharedPopulation = std::shared_ptr<Population>;
}

#endif //SRES_POPULATION_H
