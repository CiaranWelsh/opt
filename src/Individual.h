//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_INDIVIDUAL_H
#define SRES_INDIVIDUAL_H

#include "Container.h"
#include "CostFunction.h"

namespace opt {

    class Individual : public Container<double> {

    public:
        using Container<double>::Container;
        using Container<double>::operator[];

        /**
         * @brief compute the fitness based on
         */
        double evaluate(CostFunction cost);

        [[nodiscard]] const std::vector<double> &getValues() const;

        void setValues(const std::vector<double> &values);

        [[nodiscard]] double getFitness() const;

        void setFitness(double fitness);

        Individual operator()(int start, int stop);

        bool operator==(const Individual &rhs) const;

        bool operator!=(const Individual &rhs) const;

        bool operator<(const Individual &rhs) const;

        bool operator>(const Individual &rhs) const;

        bool operator<=(const Individual &rhs) const;

        bool operator>=(const Individual &rhs) const;

        /**
         * @brief performs vector addition on this
         * Individual and @param other
         */
        Individual operator+(const Individual &other);

        /**
         * @brief performs vector subtraction on this
         * Individual and @param other
         */
        Individual operator-(const Individual &other);

        /**
         * @brief performs vector multiplication on this
         * Individual and @param other
         */
        Individual operator*(const Individual &other);

        /**
         * @brief performs vector dividion on this
         * Individual and @param other
         */
        Individual operator/(const Individual &other);

        /**
         * @brief performs vector addition with scalar on this
         * Individual and @param scalar
         */
        Individual operator+(double scalar);

        /**
         * @brief performs vector addition with scalar on this
         * Individual and @param scalar
         */
        Individual operator-(double scalar);

        /**
         * @brief performs vector addition with scalar on this
         * Individual and @param scalar
         */
        Individual operator*(double scalar);

        /**
         * @brief performs vector addition with scalar on this
         * Individual and @param scalar
         */
        Individual operator/(double scalar);

    private:

        /**
         * @brief the fitness of this individual.
         */
        double fitness_ = std::numeric_limits<double>::max();

    };

}

#endif //SRES_INDIVIDUAL_H
