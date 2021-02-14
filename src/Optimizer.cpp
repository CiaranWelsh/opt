//
// Created by Ciaran on 06/02/2021.
//

#include <utility>
#include <vector>
#include <iostream>
#include "Optimizer.h"

namespace opt {

    Optimizer::Optimizer(
            opt::CostFunction cost, const std::vector<double> &startingValues,
            const std::vector<double> &lb, const std::vector<double> &ub, bool logspace,
            bool verbose)
            : cost_(cost),
              optItems_(OptItems(startingValues, lb, ub, logspace)),
              numberOfParameters_(startingValues.size()),
              verbose_(verbose){

    }

    Optimizer::Optimizer(opt::CostFunction cost, OptItems optItems)
            :
            cost_(cost),
            optItems_(std::move(optItems)),
            numberOfParameters_(optItems.size()) {}

    CostFunction Optimizer::getCost() const {
        return cost_;
    }

    void Optimizer::setCost(CostFunction cost) {
        cost_ = cost;
    }

    void Optimizer::setSeed(unsigned long long int seed) {
        RandomNumberGenerator::getInstance(seed);
    }


    double Optimizer::getBestFitnessValue() const {
        return bestFitnessValue_;
    }

    void Optimizer::setBestValue(double bestValue) {
        bestFitnessValue_ = bestValue;
    }

    int Optimizer::getNumberOfParameters() const {
        return numberOfParameters_;
    }

    void Optimizer::setNumberOfParameters(int numberOfParameters) {
        numberOfParameters_ = numberOfParameters;
    }

}


