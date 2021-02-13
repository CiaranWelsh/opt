//
// Created by Ciaran on 05/02/2021.
//

#include "SRES.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <ios>
#include <set>
#include <execution>
#include <ranges>

#define HERE   std::cout << __FILE__ << ":" << __LINE__ << std::endl;


namespace opt {
    SRES::SRES(CostFunction cost, int populationSize,
               int numGenerations, const DoubleVector &startingValues, const DoubleVector &lb,
               const DoubleVector &ub, int childrate, int stopAfterStalledGenerations, bool logspace, bool verbose,
               int numLHSInitSamples, int numGenerationsForLHSInitSamples)
            : PopulationOptimizer(
            cost, populationSize, numGenerations,
            startingValues, lb, ub, childrate,
            stopAfterStalledGenerations, logspace, verbose,
            numLHSInitSamples, numGenerationsForLHSInitSamples
    ) {
    };

    const DoubleVector &SRES::getMaxVariance() const {
        return maxVariance_;
    }

    void SRES::setMaxVariance(const DoubleVector &maxVariance) {
        maxVariance_ = maxVariance;
    }

    double SRES::getPf() const {
        return pf_;
    }

    void SRES::setPf(double pf) {
        pf_ = pf;
    }

    bool SRES::swap(size_t from, size_t to) {
        DoubleVector pTmp = population_[to];
        population_[to] = population_[from];
        population_[from] = pTmp;

        pTmp = variance_[to];
        variance_[to] = variance_[from];
        variance_[from] = pTmp;

        double dTmp = populationFitness_[to];
        populationFitness_[to] = populationFitness_[from];
        populationFitness_[from] = dTmp;

        dTmp = phi_[to];
        phi_[to] = phi_[from];
        phi_[from] = dTmp;

        return true;
    }

    bool SRES::replicate() {
        bool Continue = true;

        size_t Parent;
        size_t i, j;

        auto itSrc = population_.begin();
        auto endSrc = itSrc + populationSize_;
        auto itTarget = endSrc;
        auto itSrcVariance = variance_.begin();
        auto itTargetVariance = itSrcVariance + populationSize_;

        double *pVariance;
        double *pVarianceEnd;
        double *pParentVariance;

        // iterate over parents
        for (i = 0; itSrc != endSrc && Continue; ++itSrc, ++itSrcVariance, ++i) {
            // iterate over the child rate - 1 since the first child is the parent.
            for (j = 1; j < getChildRate(); ++j, ++itTarget, ++itTargetVariance) {
                // first just copy the individuals
                *itTarget = *itSrc;
                *itTargetVariance = *itSrcVariance;

                // do recombination on the sigma
                // since sigmas already have one parent's component
                // need only average with the sigmas of the other parent
                Parent = RandomNumberGenerator::getInstance().uniformInt(0, i + populationSize_ - 1);

                // extract the pointer to first element from itTargetVariance
                pVariance = itTargetVariance->data();
                pVarianceEnd = pVariance + numberOfParameters_;
                // extract pointer to Parent element of variance vector
                pParentVariance = variance_[Parent].data();

                for (; pVariance != pVarianceEnd; ++pVariance, ++pParentVariance)
                    *pVariance = (*pVariance + *pParentVariance) * .5;
            }
        }

        Continue &= mutate();

        return Continue;
    }

    bool SRES::replicate2() {
        bool Continue = true;

        int parent;
        int i, j;

        auto itSrc = population_.begin();
        auto endSrc = itSrc + populationSize_;
        auto itTarget = endSrc;
        auto itSrcVariance = variance_.begin();
        auto itTargetVariance = itSrcVariance + populationSize_;

        double *pVariance;
        double *pVarianceEnd;
        double *pParentVariance;

        std::vector<double> child(numberOfParameters_);
        std::vector<double> childVariance(numberOfParameters_);
        int parentIdx;

        // iterate over parents
        for (i = 0; i < populationSize_; i++) {
            // and iterate over childrate -1, since parent is the first child
            for (j = 1; j < getChildRate(); j++) {
                // first just copy parent to child
                std::copy(population_[i].begin(), population_[i].end(), child.begin());
                std::copy(variance_[i].begin(), variance_[i].end(), childVariance.begin());

                // do recombination on the sigma
                // since sigmas already have one parent's component
                // need only average with the sigmas of the other parent

                // randomly select the index of a parent
                parentIdx = RandomNumberGenerator::getInstance().uniformInt(0, i + populationSize_ - 1);

            }
        }

        // iterate over parents
        for (i = 0; itSrc != endSrc && Continue; ++itSrc, ++itSrcVariance, ++i) {
            // iterate over the child rate - 1 since the first child is the parent.
            for (j = 1; j < getChildRate(); ++j, ++itTarget, ++itTargetVariance) {
                // first just copy the individuals
                *itTarget = *itSrc;
                *itTargetVariance = *itSrcVariance;


                parent = RandomNumberGenerator::getInstance().uniformInt(0, i + populationSize_ - 1);

                // extract the pointer to first element from itTargetVariance
                pVariance = itTargetVariance->data();
                pVarianceEnd = pVariance + numberOfParameters_;
                // extract pointer to Parent element of variance vector
                pParentVariance = variance_[parent].data();

                for (; pVariance != pVarianceEnd; ++pVariance, ++pParentVariance)
                    *pVariance = (*pVariance + *pParentVariance) * .5;
            }
        }

        Continue &= mutate();

        return Continue;
    }

    bool SRES::mutate() {
        auto it = population_.begin() + populationSize_;
        auto end = population_.end();
        auto itVariance = variance_.begin() + populationSize_;

        double *pVariable, *pVariableEnd, *pVariance, *pMaxVariance;
//        double *pPhi = mPhi.array() + populationSize_;
        double *pPhi = &phi_[0] + populationSize_;
        double *pValue = &populationFitness_[0] + populationSize_;

        bool Continue = true;
        size_t i, j;
        double v1;

        // Mutate each new individual
        for (i = populationSize_; it != end && Continue; ++it, ++itVariance, ++i) {
            pVariable = it->data();
            pVariableEnd = pVariable + numberOfParameters_;
            pVariance = itVariance->data();
            pMaxVariance = maxVariance_.data();

            v1 = RandomNumberGenerator::getInstance().normal(0, 1);

            for (j = 0; pVariable != pVariableEnd; ++pVariable, ++pVariance, ++pMaxVariance, ++j) {
                double &mut = *pVariable;
                double Store = mut;


                const OptItem &OptItem = optItems_[j];

                size_t l = std::numeric_limits<size_t>::max();

                try {
                    // update the parameter for the variances
                    *pVariance = std::min(*pVariance * exp(
                            tauPrime_ * v1 + tau_ * RandomNumberGenerator::getInstance().normal(0, 1)
                    ), *pMaxVariance);

                    for (l = 0; l < 10; l++) {
                        // calculate the mutated parameter
                        mut = Store + *pVariance * RandomNumberGenerator::getInstance().normal(0, 1);

                        if (OptItem.checkConstraint(mut) == 0)
                            break;
                    }
                }

                catch (...) {
                    mut = (OptItem.getUb() + OptItem.getLb()) * 0.5;
                }

                if (l == 10)
                    mut = Store;

                /**
                 * todo The below was in the original code. Currently not sure if this applied to us.
                 */
                // We need to set the value here so that further checks take
                // account of the value.
                // *mProblemContext.master()->getContainerVariables()[j] = (mut);
            }

            // calculate its fitness
            Continue = evaluate(*it);
            *pValue++ = fitnessValue_;
            *pPhi++ = phi(i);
        }

        return Continue;
    }


    // evaluate the distance of parameters and constraints to boundaries
    double SRES::phi(size_t indivNum) {
        double phiVal = 0.0;
        double phiCalc;

        const std::vector<double> &indv = population_[indivNum];

//        for (auto &optItem: optItems_){
//            // check constraint lb
//            if (optItem.getValue() < optItem.getLb()){
//                phiCalc = optItem.getLb() -
//            }
//
//            if (optItem.getValue() > optItem.getUb()){
//
//            }
//
//        }

        auto it = optItems_.begin();
        auto end = optItems_.end();
        double *pValue = population_[indivNum].data();

        for (; it != end; ++it, pValue++) {
            switch (it->checkConstraint()) {
                case -1:
                    phiCalc = it->getLb() - *pValue;
                    phiVal += phiCalc * phiCalc;
                    break;

                case 1:
                    phiCalc = *pValue - it->getLb();
                    phiVal += phiCalc * phiCalc;
                    break;
            }
        }

        /**
         * If / when we add constraints into the fray, we add them here.
         */
        // it = mProblemContext.master()->getConstraintList().begin();
        // end = mProblemContext.master()->getConstraintList().end();
        // for (; it != end; ++it) {
        //     phiCalc = (*it)->getConstraintViolation();
        //     if (phiCalc > 0.0)
        //         phiVal += phiCalc * phiCalc;
        // }

        return phiVal;
    }

    bool SRES::initialize() {
        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        size_t i, j;

        if (pf_ < 0.0 || 1.0 < pf_) {
            pf_ = 0.475;
        }

        // sample using lhs for init population.
        RandomNumberGenerator rng = RandomNumberGenerator::getInstance();
        population_ = rng.lhs(
                populationSize_ * childRate_,
                numberOfParameters_,
                optItems_.getLb(),
                optItems_.getUb()
        );

        // set the first individual in population_ to be the initial guess provided by user
        population_[0] = optItems_.getStartingValues();

        variance_ = std::vector<std::vector<double>>(
                populationSize_ * childRate_, std::vector<double>(numberOfParameters_));

        maxVariance_.resize(numberOfParameters_);

        for (i = 0; i < numberOfParameters_; i++) {
            const OptItem &optItem = optItems_[i];
            try {
                maxVariance_[i] =
                        (optItem.getUb() - optItem.getLb()) / sqrt(double(numberOfParameters_));
            }
            catch (...) {
                maxVariance_[i] = 1.0e3;
            }
        }

        populationFitness_.resize(childRate_ * populationSize_);
        populationFitness_.assign(populationFitness_.size(), std::numeric_limits<double>::infinity());
        bestFitnessValue_ = std::numeric_limits<double>::infinity();
        hallOfFame_.push_back(bestFitnessValue_);

        phi_.resize(childRate_ * populationSize_);

        double alpha = 0.2;
        double chi = 1 / (2 * sqrt(double(numberOfParameters_))) + 1 / (2 * double(numberOfParameters_));
        double varphi = sqrt(2 / chi * log(1 / alpha) * exp(chi / 2 - (1 - alpha)));

//            double varphi = 1; // or just set varphi to 1
        tau_ = varphi / sqrt(2 * sqrt(double(numberOfParameters_)));
        tauPrime_ = varphi / sqrt(2 * double(numberOfParameters_));

        return true;
    }

    void checkBoundaries(std::mutex &mutex, const OptItem &optItem, double &mut) {
        mutex.lock();
//        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        switch (optItem.checkConstraint(mut)) {
            case -1:
                mut = optItem.getLb();
                if (!optItem.checkLowerBound(mut)) { // Inequality
                    if (mut == 0.0)
                        mut = std::numeric_limits<double>::min();
                    else
                        mut += mut * std::numeric_limits<double>::epsilon();
                }
                break;

            case 1:
                mut = optItem.getUb(); // should log stuff in optItem instead.
                if (!optItem.checkUpperBound(mut)) {// Inequality
                    if (mut == 0.0)
                        mut = -std::numeric_limits<double>::min();
                    else
                        mut -= mut * std::numeric_limits<double>::epsilon();
                }
                break;
        }
        mutex.unlock();
    }

    // Initialize the population
    bool SRES::creation() {
        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        size_t i;
        size_t j;

        double mn;
        double mx;
        double la;

        bool Continue = true;

        std::mutex mutex;
        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        // set the first individual to the initial guess (starting values)
        for (j = 0; j < numberOfParameters_; j++) {
            const OptItem &optItem = optItems_[j];

            double mut = optItem.getStartingValue();

            // force it to be within the bounds
            //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            checkBoundaries(mutex, optItem, mut);
            //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

            // Set the variance for this parameter.
            variance_[0][j] = std::min(
                    optItem.getUb() - mut,
                    mut - optItem.getLb()) / sqrt(double(numberOfParameters_));
        }
        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        // update stats for first element in population
        Continue = evaluate(*population_.begin());
        populationFitness_[0] = fitnessValue_;
        phi_[0] = phi(0);
        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        i = 0;
        std::for_each(std::execution::seq, population_.begin(), population_.end(),
                      [this, &i, &mutex](std::vector<double> &indv) {
                          //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                          int j = 0;
                          std::for_each(std::execution::seq, indv.begin(), indv.end(),
                                        [this, i, &j, &mutex](double mut) {
                                            const OptItem &optItem = optItems_[j];

                                            // calculate lower and upper bounds
                                            double mn = optItem.getLb();
                                            double mx = optItem.getUb();
                                            double la;
                                            //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                                            try {
                                                // First determine the location of the intervall
                                                // Secondly determine whether to distribute the parameter linearly or not
                                                // depending on the location and act uppon it.

                                                // the interval [mn, mx) is in [0, inf)
                                                if (0.0 <= mn) {
                                                    la = log10(mx) -
                                                         log10(std::max(mn, std::numeric_limits<double>::min()));
                                                    //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                                                    if (la < 1.8 || mn <= 0.0) // linear
                                                        mut = mn +
                                                              RandomNumberGenerator::getInstance().uniformReal(0, 1) *
                                                              (mx - mn);
                                                    else
                                                        mut = pow(10.0, log10(std::max(mn,
                                                                                       std::numeric_limits<double>::min())) +
                                                                        la *
                                                                        RandomNumberGenerator::getInstance().uniformReal(
                                                                                0, 1));
                                                }
                                                    // 0 is in the interval (mn, mx)
                                                else if (mx > 0) {
                                                    //std::cout << __FILE__ << ":" << __LINE__ << std::endl;
                                                    la = log10(mx) + log10(-mn);

                                                    if (la < 3.6) // linear
                                                        mut = mn +
                                                              RandomNumberGenerator::getInstance().uniformReal(0, 1) *
                                                              (mx - mn);
                                                    else {
                                                        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                                                        double mean = (mx + mn) * 0.5;
                                                        double sigma = mean * 0.01;

                                                        do {
                                                            mut = RandomNumberGenerator::getInstance().normal(mean,
                                                                                                              sigma);
                                                        } while ((mut < mn) || (mut > mx));
                                                    }

                                                } else { //// the interval (mn, mx] is in (-inf, 0]
                                                    // Switch lower and upper bound and change sign, i.e.,
                                                    // we can treat it similarly as location 1:
                                                    mx = -optItem.getLb();
                                                    mn = -optItem.getUb();

                                                    la = log10(mx) -
                                                         log10(std::max(mn, std::numeric_limits<double>::min()));

                                                    if (la < 1.8 || mn <= 0.0) // linear
                                                        mut = -(mn +
                                                                RandomNumberGenerator::getInstance().uniformReal(0, 1) *
                                                                (mx - mn));
                                                    else
                                                        mut = -pow(10.0, log10(std::max(mn,
                                                                                        std::numeric_limits<double>::min())) +
                                                                         la *
                                                                         RandomNumberGenerator::getInstance().uniformReal(
                                                                                 0, 1));
                                                }
                                            }

                                            catch (...) {
                                                mut = (mx + mn) * 0.5;
                                            }
                                            //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                                            // force it to be within the bounds
//                                            checkBoundaries(mutex, optItem, mut);
                                            switch (optItem.checkConstraint(mut)) {
                                                case -1:
                                                    mut = optItem.getLb();
                                                    if (!optItem.checkLowerBound(mut)) { // Inequality
                                                        if (mut == 0.0)
                                                            mut = std::numeric_limits<double>::min();
                                                        else
                                                            mut += mut * std::numeric_limits<double>::epsilon();
                                                    }
                                                    break;

                                                case 1:
                                                    mut = optItem.getUb(); // should log stuff in optItem instead.
                                                    if (!optItem.checkUpperBound(mut)) {// Inequality
                                                        if (mut == 0.0)
                                                            mut = -std::numeric_limits<double>::min();
                                                        else
                                                            mut -= mut * std::numeric_limits<double>::epsilon();
                                                    }
                                                    break;
                                            }
                                            //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

                                            // Set the variance for this parameter.
                                            this->variance_[i][j] = std::min(
                                                    optItem.getUb() - mut,
                                                    mut - optItem.getLb()) / sqrt(double(numberOfParameters_));
                                            j++; // increment j
                                        });
                          populationFitness_[i] = (*cost_)(indv.data());
                          phi_[i] = phi(i);
                          i++;

                      });

        return Continue;
    }

    // check the best individual at this generation
    int SRES::findBestIndividual() {
        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;

        size_t i, bestIndex = std::numeric_limits<size_t>::max();
        double bestValue = std::numeric_limits<double>::max();

        for (i = 0; i < population_.size(); i++)
            // todo : (cw) original copasi code used the following condition
            //  requiring phi_ to be 0 before best value can be updated.
            //  In the original code, phi was always 0. Not sure why (probably worth finding out).
            //  But, I've modified phi_ so that it produces values, which seems right, and therefore phi_ is never 0.
            //  Note that I didn not modify phi explicitely. Instead I remove the silly dependency on complicated
            //  iterators and it worked. In fact, I think the copasi code is buggy in this regard. Its not suprising
            //  that mistakes were made, given the stupid iterator filled confusing crappy code that was the original.
            //  Thus, I must remove the phi_[i] == 0 requirement for a individual to become best.
            // if (populationFitness_[i] < bestValue && phi_[i] == 0) {
            if (populationFitness_[i] < bestValue) {
                bestValue = populationFitness_[i];
                bestIndex = i;
                solutionValues_ = population_[i];
            }

        return bestIndex;
    }

    void SRES::select() {
        //std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        size_t i, j;
        bool wasSwapped;

        // Selection Method for Stochastic Ranking
        // stochastic ranking "bubble sort"

        for (i = 0; i < population_.size(); i++) {
            wasSwapped = false;

            // :TODO: since we are only interested in mPopulationSize highest ranked
            //    individuals the upper limit of the loop can be improved.
            // lambda is number of individuals
            RandomNumberGenerator rng = RandomNumberGenerator::getInstance();
            for (j = 0; j < population_.size() - 1; j++) {
                // within bounds || random chance to compare values outside bounds
                if ((phi_[j] == 0 && phi_[j + 1] == 0) || (rng.uniformReal(0, 1) < pf_)) {
                    // compare obj fcn using mValue alternative code
                    if (populationFitness_[j] > populationFitness_[j + 1]) {
                        swap(j, j + 1);
                        wasSwapped = true;
                    }
                } else {
                    if (phi_[j] > phi_[j + 1]) {// j further outside then j+1
                        swap(j, j + 1);
                        wasSwapped = true;
                    }
                }
            }
            // if nothing was swapped, then they're ordered!
            if (!wasSwapped) break;
        }
    }

    bool SRES::fit() {
        HERE;
        bool Continue = true;
        HERE;
        size_t bestIndex;
        HERE;

        size_t Stalled = 0;
        HERE;

        if (!initialize()) {
            // comment out mpCallBack code for now. Its to do with
            // logging the results and I may roll my own.
            // if (mpCallBack)
            //    mpCallBack->finishItem(mhGenerations);
            HERE;

            return false;
        }

        // initialise the population
        Continue = creation();
        HERE;

        if (bestFitnessValue_ == -std::numeric_limits<double>::infinity())
            Continue = false;

        // get the index of the fittest
        bestIndex = findBestIndividual();
        HERE;

        if (bestIndex != std::numeric_limits<size_t>::max()) {
            // and store that value
            bestFitnessValue_ = populationFitness_[bestIndex];
            solutionValues_ = population_[bestIndex];
            hallOfFame_.push_back(populationFitness_[bestIndex]);

            if (bestFitnessValue_ == -std::numeric_limits<double>::infinity())
                Continue = false;
            HERE;


            // todo will need something to replace this
            // We found a new best value lets report it.
            // mpParentTask->output(COutputInterface::DURING);
        }

        if (!Continue) {
            // if (mpCallBack)
            //    mpCallBack->finishItem(mhGenerations);
            HERE;

            return true;
        }
        HERE;

        for (currentGeneration_ = 2;
             currentGeneration_ <= numGenerations_ && Continue;
             currentGeneration_++, Stalled++) {
            HERE;

            if (stopAfterStalledGenerations_ != 0 && Stalled > stopAfterStalledGenerations_)
                break;

            Continue = replicate();
            HERE;

            // select the most fit
            select();
            HERE;

            // get the index of the fittest
            bestIndex = findBestIndividual();
            HERE;

            if (bestIndex != std::numeric_limits<size_t>::max() && populationFitness_[bestIndex] < bestFitnessValue_) {
                HERE;
                // and store that value
                bestFitnessValue_ = populationFitness_[bestIndex];
                hallOfFame_.push_back(populationFitness_[bestIndex]);
                solutionValues_ = population_[bestIndex];
                if (bestFitnessValue_ == -std::numeric_limits<double>::infinity())
                    Continue = false;

                if (verbose_) {
                    printCurrent();
                }

                // if (mpCallBack)
                //    Continue = mpCallBack->progressItem(mhGenerations);

                //use a different output channel. It will later get a proper enum name
                // mpParentTask->output(COutputInterface::MONITORING);
            }

            //if (mLogVerbosity > 0)
            //    mMethodLog.enterLogEntry(
            //            COptLogEntry("Algorithm finished.",
            //                         "Terminated after " + std::to_string(currentGeneration_ - 1) + " of " +
            //                         std::to_string(mGenerations) + " generations."));

            //if (mpCallBack)
            //    mpCallBack->finishItem(mhGenerations);

        }
        HERE;

        return true;
    }

    void SRES::printCurrent() {
        HERE;
        std::cout << "current generation: " << currentGeneration_ << "; ";

        if (logspace_) {
            HERE;
            std::cout << "best objective value: " << pow(10, bestFitnessValue_) << std::endl;

        } else {
            HERE;
            std::cout << "best objective value: " << bestFitnessValue_ << std::endl;

        }
        HERE;

    }


}
