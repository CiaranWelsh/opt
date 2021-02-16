//
// Created by Ciaran on 16/02/2021.
//

#include "DiffEvolutionSelection.h"
#include "Error.h"

namespace opt {

    void DiffEvolutionSelection::select() {

        for (int i=0; i<population_->size(); i++){
            if ((*nextGen_)[i].getFitness() == std::numeric_limits<double>::max()){
                RUNTIME_ERROR << "nextGen has not been evaluated" << std::endl;
            }
            if ((*population_)[i].getFitness() == std::numeric_limits<double>::max()){
                RUNTIME_ERROR << "population has not been evaluated" << std::endl;
            }
            if ((*nextGen_)[i].getFitness() < (*population_)[i].getFitness()){
                // we do nothing, since we keep the next gen vector in place
            } else {
                // we put back the original vector, since it was better
                (*nextGen_)[i] = (*population_)[i];
            }

        }

    }
}