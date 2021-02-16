//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_MUTATION_H
#define SRES_MUTATION_H

#include "Operator.h"
#include "OptItems.h"

namespace opt {

    class Mutation : public Operator {

    public:

        using Operator::Operator;

        explicit Mutation(SharedPopulation population);

        Mutation(SharedPopulation population, SharedPopulation nextGen);

        Mutation(SharedPopulation population, SharedPopulation nextGen, OptItems* optItems);

        /**
         * @brief virtual default destructor
         */
        virtual ~Mutation() = default;

        virtual void mutate() = 0;

        [[nodiscard]] OptItems *getOptItems() const;

        void setOptItems(OptItems *optItems);

    protected:
        /**
         * Non owning pointer to OptItems so we can check
         * boundaries during mutations
         */
        OptItems *optItems_;

    };
}


#endif //SRES_MUTATION_H
