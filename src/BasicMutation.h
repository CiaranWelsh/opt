//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_BASICMUTATION_H
#define SRES_BASICMUTATION_H

#include "Mutation.h"

namespace opt {

    class BasicMutation : public Mutation {
    public:

        using Mutation::Mutation;

        ~BasicMutation() override = default;

        void mutate() override;

    };
}


#endif //SRES_BASICMUTATION_H
