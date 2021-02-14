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

        TourneySelection(SharedPopulation population, int tournsize, int k);

        ~TourneySelection() override = default;

        std::vector<int> select() override;

    private:
        int k_;
        int tournsize_;
    };

}

#endif //SRES_TOURNEYSELECTION_H
