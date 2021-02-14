//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_INDIVIDUAL_H
#define SRES_INDIVIDUAL_H

#include "Container.h"

namespace opt {

    class Individual : public Container<double> {

    public:
        using Container<double>::Container;
        using Container<double>::operator[];

        [[nodiscard]] const std::vector<double> &getValues() const;

        void setValues(const std::vector<double> &values);

        [[nodiscard]] double getFitness() const;

        void setFitness(double fitness);

        Individual operator()(int start, int stop);

        Individual& operator+(Individual& other);

        bool operator==(const Individual &rhs) const;

        bool operator!=(const Individual &rhs) const;

        bool operator<(const Individual &rhs) const;

        bool operator>(const Individual &rhs) const;

        bool operator<=(const Individual &rhs) const;

        bool operator>=(const Individual &rhs) const;

    private:

        /**
         * @brief the fitness of this individual.
         */
        double fitness_ = std::numeric_limits<double>::max();

    };

}

#endif //SRES_INDIVIDUAL_H
