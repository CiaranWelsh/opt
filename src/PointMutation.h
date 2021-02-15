//
// Created by Ciaran on 14/02/2021.
//

#ifndef OPT_POINTMUTATION_H
#define OPT_POINTMUTATION_H

#include "Mutation.h"

namespace opt {


    class PointMutation : public Mutation{

    public:
        using Mutation::Mutation;

        explicit PointMutation(double pb);

        void mutate() override;

    private:
        double pb_;
    };

}

#endif //OPT_POINTMUTATION_H
