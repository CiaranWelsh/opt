//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_CROSSOVER_H
#define SRES_CROSSOVER_H

namespace opt {


    class CrossOver {

    public:

        /**
         * @brief default constructor
         */
         CrossOver() = default;

         virtual ~CrossOver() = default;

         virtual void replicate() = 0;

    };
}

#endif //SRES_CROSSOVER_H
