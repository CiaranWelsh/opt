//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_SELECTION_H
#define SRES_SELECTION_H

#include "Population.h"
#include "Operator.h"

namespace opt {

    class Selection : public Operator {
        
    public:

        using Operator::Operator;

        /**
         * @brief construct a selection operator
         * @param howMany how many individuals to propagate to next generation
         */
        Selection(SharedPopulation population, int howMany);

        /**
         * @brief constructor for initializing
         * Selection operator without a population. This is
         * a requirement of dependency injection for operators
         * into algorithms.
         */
        explicit Selection(int howMany, int numEstimatedParameters);

        [[nodiscard]] int howMany() const;

        void setHowMany(int howMany);

        virtual ~Selection() = default;

        virtual void select() = 0;


    protected:
        int howMany_;

    };

}

#endif //SRES_SELECTION_H
