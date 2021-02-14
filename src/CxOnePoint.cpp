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
}
