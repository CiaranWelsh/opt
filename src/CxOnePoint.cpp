//
// Created by Ciaran on 14/02/2021.
//

#include "CxOnePoint.h"
#include "RandomNumberGenerator.h"

namespace opt{

    void CxOnePoint::crossover(Individual &parent1, Individual &parent2) {
        int size = parent1.size();
        int index;
        // when nparams is 1 do nothing
        if (size == 1){
            return;
        } else if(size == 2){
            // swap components
            double tmp = parent1[1];
            parent1[1] = parent2[1];
            parent2[1] = tmp;
            return;
        } else if (size == 3){
            // then we always pick index 1
            index = 1;
        } else {
            index = RandomNumberGenerator::getInstance().uniformInt(1, size-1);
        }
        Individual parent1_section1 = parent1(0, index);
        Individual parent1_section2 = parent1(index, parent1.size()-1);

        Individual parent2_section1 = parent2(0, index);
        Individual parent2_section2 = parent2(index, parent1.size()-1);

        parent1 = parent1_section1 + parent2_section1;
        parent2 = parent1_section2 + parent2_section2;

    }

        void CxOnePoint::crossover() {
        // we'll have already selected the population.
        int numParentsToMate = population_->size();
        if (numParentsToMate % 2 == 1){
            // only do even sized populations
            numParentsToMate = numParentsToMate - 1;
        }
        // shuffle indices. then take pairs. If odd, don't do last one.
        std::vector<int> idx(numParentsToMate);
        for (int i=0; i < numParentsToMate; i++){
            idx[i] = i;
        }
        std::shuffle(idx.begin(), idx.end(), RandomNumberGenerator::getInstance().getGenerator());

        for (auto[i, j] = std::tuple(0, 1); j < numParentsToMate; i+=2, j+=2) {
            int parent1idx = idx[i];
            int parent2idx = idx[j];
            crossover((*population_)[parent1idx], (*population_)[parent2idx]);
        }
    }

}
