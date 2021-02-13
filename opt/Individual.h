//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_INDIVIDUAL_H
#define SRES_INDIVIDUAL_H

#include <vector>

namespace opt {

    class Individual : public std::vector<double> {

    public:
        using std::vector<double>::vector;

    };

}

#endif //SRES_INDIVIDUAL_H
