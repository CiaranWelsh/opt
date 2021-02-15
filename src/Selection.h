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
        explicit Selection(int howMany);

        int getHowMany() const;

        void setHowMany(int howMany);

        virtual ~Selection() = default;

        virtual void select(SharedPopulation &nextGen) = 0;

    private:
        int howMany_;

    };

}

#endif //SRES_SELECTION_H
