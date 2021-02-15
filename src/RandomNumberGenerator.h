//
// Created by Ciaran on 05/02/2021.
//

#ifndef SRES_RANDOMNUMBERGENERATOR_H
#define SRES_RANDOMNUMBERGENERATOR_H

#include <chrono>
#include <vector>
#include <random>

namespace opt {


    /**
     * @brief A singleton Random number generator. We only want one
     * random number generator as if we instantiate multiple
     * then we'll get a repeated predictable sequence of numbers.
     */
    class RandomNumberGenerator {

    public:

        static RandomNumberGenerator &getInstance(unsigned long long seed = 0);

        double uniformReal(double lb, double ub);

        std::vector<double> uniformReal(double lb, double ub, int size);

        double normal(double mu, double sigma);

        std::vector<double> normal(double mu, double sigma, int size);

        int uniformInt(int lb, int ub);

        std::vector<int> uniformInt(int lb, int ub, int size);

        /**
         * @brief produce a matrix of numbers sampled
         * according to latin hypercode sampling with shape=(npopulation, nparams).
         */
        std::vector<std::vector<double>> lhs(int npopulation, int nparams);

        /**
         * @brief Alternative overload of lhs algorithm where the ranges provided
         * by the lb and ub vector arguments are used. Sampling can be done in logspace.
         */
        std::vector<std::vector<double>> lhs(
                int npopulation, int nparams, const std::vector<double>& lb,const  std::vector<double>& ub, bool sampleInLogspace = true);

        std::vector<int> uniformIntWithoutReplacement(int lb, int ub, int size);

    private:

        explicit RandomNumberGenerator(
                unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count());

        std::default_random_engine generator_;


    };

}

#endif //SRES_RANDOMNUMBERGENERATOR_H
