//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_SELECTION_H
#define SRES_SELECTION_H

namespace opt {

    class Selection {

    public:

        /**
         * @brief default constructor
         */
         Selection() = default;

         virtual ~Selection() = default;

         virtual void select() = 0;

    };

}

#endif //SRES_SELECTION_H
