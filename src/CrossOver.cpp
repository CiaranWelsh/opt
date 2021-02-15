//
// Created by Ciaran on 12/02/2021.
//

#include "CrossOver.h"
#include "RandomNumberGenerator.h"

namespace opt{

    void CrossOver::crossover() {
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