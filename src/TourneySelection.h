//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_TOURNEYSELECTION_H
#define SRES_TOURNEYSELECTION_H

#include "Selection.h"

namespace opt {


    class TourneySelection : public Selection {
    public:

        using Selection::Selection;

        ~TourneySelection() override = default;

        void select() override;
    };

}

#endif //SRES_TOURNEYSELECTION_H
