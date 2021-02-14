//
// Created by Ciaran on 14/02/2021.
//

#ifndef OPT_COSTFUNCTION_H
#define OPT_COSTFUNCTION_H


namespace opt {

    /**
     * @brief cost function with signature for parameters (to estimate).
     * @param individual or genome. This is a double vector representing candiate parameters
     * @return Fitness of the input individual.
     */
    typedef double(*CostFunction)(double *);
}

#endif //OPT_COSTFUNCTION_H
