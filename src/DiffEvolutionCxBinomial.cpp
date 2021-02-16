//
// Created by Ciaran on 16/02/2021.
//

#include "DiffEvolutionCxBinomial.h"

#include "RandomNumberGenerator.h"


namespace opt {

    DiffEvolutionCxBinomial::DiffEvolutionCxBinomial(SharedPopulation population, SharedPopulation nextGen, double pb)
            : CrossOver(std::move(population), std::move(nextGen)), pb_(pb) {}

    void DiffEvolutionCxBinomial::crossover() {
        int indSize = (*population_)[0].size();
        for (int i=0; i< population_->size(); i++){
            for (int j=0; j<indSize; j++){
                double r = RandomNumberGenerator::getInstance().uniformReal(0, 1);
                int jrand = RandomNumberGenerator::getInstance().uniformInt(0, indSize);
                if (r <= pb_ || j == jrand){
                    // accept the mutated gene, which we already have in nextGen
                } else {
                    // we revert back to what we had before mutation
                    (*nextGen_)[i][j] = (*population_)[i][j];
                }
            }
        }
    }

    double DiffEvolutionCxBinomial::getPb() const {
        return pb_;
    }

    void DiffEvolutionCxBinomial::setPb(double pb) {
        pb_ = pb;
    }


}


