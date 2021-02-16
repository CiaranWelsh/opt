//
// Created by Ciaran on 16/02/2021.
//

#ifndef OPT_DIFFEVOLUTIONSELECTION_H
#define OPT_DIFFEVOLUTIONSELECTION_H

#include "RandomNumberGenerator.h"
#include "Selection.h"

namespace opt {

    class DiffEvolutionSelection : public Selection {
    public:
        using Selection::Selection;

        /**
         * @brief Select using the standard differential evolution
         * selection operator. A new vector from nextGen_ that has
         * been mutated and crossover is chosen if its fitness is
         * better than the original. Otherwise, the original is kept.
         */
        void select() override;

    };

}

#endif //OPT_DIFFEVOLUTIONSELECTION_H
