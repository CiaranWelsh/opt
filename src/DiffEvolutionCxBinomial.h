//
// Created by Ciaran on 16/02/2021.
//

#ifndef OPT_DIFFEVOLUTIONCXBINOMIAL_H
#define OPT_DIFFEVOLUTIONCXBINOMIAL_H

#include "CrossOver.h"



namespace opt {

    class DiffEvolutionCxBinomial : public CrossOver {
    public:

        using CrossOver::CrossOver;

        /**
         * @brief constructor for DiffEvolutionCxBinomial where
         * @param population is the SharedPopulation to crossover
         * and @param pb is the prob of crossover, i.e. the crossover
         * rate
         */
        DiffEvolutionCxBinomial(SharedPopulation population, SharedPopulation nextGen, double pb);

        void crossover(Individual &parent1, Individual &parent2) override{};

        void crossover() override;

        double getPb() const;

        void setPb(double pb);

    private:
        /**
         * Crossover rate
         */
        double pb_;
    };

}


#endif //OPT_DIFFEVOLUTIONCXBINOMIAL_H
