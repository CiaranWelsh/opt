//
// Created by Ciaran on 12/02/2021.
//

#include "Individual.h"

#include <vector>

namespace opt {
    const std::vector<double> &Individual::getValues() const {
        return contents_;
    }

    void Individual::setValues(const std::vector<double> &contents) {
        contents_ = contents;
    }

    double Individual::getFitness() const {
        return fitness_;
    }

    void Individual::setFitness(double fitness) {
        fitness_ = fitness;
    }

    bool Individual::operator==(const Individual &rhs) const {
        return static_cast<const opt::Container<double> &>(*this) == static_cast<const opt::Container<double> &>(rhs) &&
               fitness_ == rhs.fitness_;
    }

    bool Individual::operator!=(const Individual &rhs) const {
        return !(rhs == *this);
    }

    bool Individual::operator<(const Individual &rhs) const {
        return fitness_ < rhs.fitness_;
    }

    bool Individual::operator>(const Individual &rhs) const {
        return rhs < *this;
    }

    bool Individual::operator<=(const Individual &rhs) const {
        return !(rhs < *this);
    }

    bool Individual::operator>=(const Individual &rhs) const {
        return !(*this < rhs);
    }

    Individual Individual::operator()(int start, int stop) {
        return Individual(std::vector<double>(contents_.begin()+start, contents_.begin()+stop));
    }

    Individual& Individual::operator+(Individual& other) {
        for (int i=0; i< other.size(); i++){
            contents_.push_back(other[i]);
        }
        return *this;
    }

}
