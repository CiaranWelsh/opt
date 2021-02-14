//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_SELECTION_H
#define SRES_SELECTION_H

#include "Population.h"
#include "Operator.h"

namespace opt {

    class Selection : public Operator {
        
    public:

        using Operator::Operator;

        virtual ~Selection() = default;

        virtual std::vector<int> select() = 0;

    };

}

#endif //SRES_SELECTION_H
