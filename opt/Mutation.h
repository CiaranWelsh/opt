//
// Created by Ciaran on 12/02/2021.
//

#ifndef SRES_MUTATION_H
#define SRES_MUTATION_H

namespace opt {

    class Mutation {

    public:

        /**
         * @brief default constructor
         */
        Mutation() = default;

        /**
         * @brief virtual default destructor
         */
        virtual ~Mutation() = default;

        virtual void mutate() = 0;


    };
}


#endif //SRES_MUTATION_H
