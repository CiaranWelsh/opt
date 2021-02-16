//
// Created by Ciaran on 15/02/2021.
//

#ifndef OPT_DIFFEVOLUTIONMUTATION1_H
#define OPT_DIFFEVOLUTIONMUTATION1_H

#include "Mutation.h"

namespace opt {

    /**
     * @brief Differential evolution mutation operator
     */
    class DiffEvolutionMutation1 : public Mutation {

    public:
        using Mutation::Mutation;

        /**
         * @brief constructor for differential evolution mutation operator
         * @param F controls the amplitude of difference vectors. Usually between [0, 2].
         */
        DiffEvolutionMutation1(SharedPopulation population, SharedPopulation nextGen, double F);

        void mutate() override;

        double getF() const;

        void setF(double f);

    private:
        double F_;

    };

}

#endif //OPT_DIFFEVOLUTIONMUTATION1_H
