//
// Created by Ciaran on 14/02/2021.
//

#ifndef OPT_TESTFUNCTIONS_H
#define OPT_TESTFUNCTIONS_H


/**
 * minimum = f(3, 0.5) = 0
 */
double BealeFunction(double* parameters) {
    double x = parameters[0];
    double y = parameters[1];
    double first = pow(1.5 - x + x*y, 2);
    double second = pow(2.25 - x + x*pow(y, 2), 2);
    double third = pow(2.625 - x + x*pow(y, 3), 2);
    return first + second + third;
};

/**
 * minimum = f(3, 0.5) = 0
 */
double BealeFunctionLog10(double* parameters) {
    double x = pow(10, parameters[0]);
    double y = pow(10, parameters[1]);
    double first = pow(1.5 - x + x*y, 2);
    double second = pow(2.25 - x + x*pow(y, 2), 2);
    double third = pow(2.625 - x + x*pow(y, 3), 2);
    return first + second + third;
};


#endif //OPT_TESTFUNCTIONS_H
