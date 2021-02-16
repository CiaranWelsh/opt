//
// Created by Ciaran on 12/02/2021.
//

#include "Individual.h"

#include <vector>

namespace opt {

    double Individual::evaluate(CostFunction cost) {
        fitness_ = (*cost)(data());
        return fitness_;
    }

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
        return contents_ == rhs.contents_;
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
        return Individual(std::vector<double>(contents_.begin() + start, contents_.begin() + stop));
    }

    Individual Individual::operator+(const Individual &other) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] + other.contents_[i];
        }
        return out;
    }

    Individual Individual::operator-(const Individual &other) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] - other.contents_[i];
        }
        return out;
    }

    Individual Individual::operator*(const Individual &other) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] * other.contents_[i];
        }
        return out;
    }

    Individual Individual::operator/(const Individual &other) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] / other.contents_[i];
        }
        return out;
    }

    Individual Individual::operator+(double scalar) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] + scalar;
        }
        return out;
    }

    Individual Individual::operator-(double scalar) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] - scalar;
        }
        return out;
    }

    Individual Individual::operator*(double scalar) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] * scalar;
        }
        return out;
    }

    Individual Individual::operator/(double scalar) {
        Individual out(size());
        for (int i = 0; i < size(); i++) {
            out[i] = contents_[i] / scalar;
        }
        return out;
    }


}
