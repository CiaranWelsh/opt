//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_TOURNEYSELECTION_H
#define SRES_TOURNEYSELECTION_H

#include "Selection.h"

namespace opt {


    /**
     * Select best individual from tournsize tournaments, k times.
     */
    class TourneySelection : public Selection {
    public:

        using Selection::Selection;

        TourneySelection(SharedPopulation population, int tournsize, int howMany);

        /**
         * @brief constructor that bypasses initialising the
         * population. We need to do this for dependency injection
         * of operators into algorithms.
         */
        TourneySelection(int tournsize, int howMany, int numEstimatedParams);

        ~TourneySelection() override = default;

        void select() override;

    private:
        int tournsize_;
    };

}

#endif //SRES_TOURNEYSELECTION_H
