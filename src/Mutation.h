//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_MUTATION_H
#define SRES_MUTATION_H

#include "Operator.h"

namespace opt {

    class Mutation : public Operator {

    public:

        using Operator::Operator;

        /**
         * @brief virtual default destructor
         */
        virtual ~Mutation() = default;

        virtual void mutate() = 0;


    };
}


#endif //SRES_MUTATION_H
