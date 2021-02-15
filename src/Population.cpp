//
// Created by Ciaran on 12/02/2021.
//

#include "Population.h"
#include <algorithm>
#include <execution>
#include "RandomNumberGenerator.h"
#include "BlockingQueue.h"
#include <thread>
#include <mutex>
#include <future>
#include <utility>
#include <iostream>

namespace opt {

    Population::Population(int npop, int nparam) {
        std::vector<Individual> ind(npop);
        for (int i = 0; i < npop; i++) {
            ind[i] = Individual(nparam);
        }
        contents_ = ind;
    };

    Population::Population(const std::vector<std::vector<double>> &input) {
        std::vector<Individual> ind;
        for (auto &it: input) {
            contents_.emplace_back(it);
        }

    }

    Population::Population(std::initializer_list<std::initializer_list<double>> input) {
        std::vector<Individual> ind;
        for (auto &it: input) {
            contents_.emplace_back(it);
        }
    }

    Population Population::fromLHS(
            int npop, int nparams,
            std::vector<double> lb, std::vector<double> ub, bool logspace) {
        RandomNumberGenerator rng = RandomNumberGenerator::getInstance();

        auto vectorPopulation = rng.lhs(npop, nparams, std::move(lb), std::move(ub), logspace);
        Population population(npop, nparams); // preallocate empty

        // use a queue. ncores - 1 to account for main thread.
        BlockingQueue<std::shared_future<Individual>> q((int) std::thread::hardware_concurrency() - 1);

        auto makeIndividual = [](std::vector<double> v) {
            return Individual(std::move(v));
        };

        std::thread addToQueueThread([&]() {
            for (int i = 0; i < npop; i++) {
                std::shared_future f = std::async(std::launch::async, makeIndividual, vectorPopulation[i]);
                q.push(f);
            }
        });

        for (int i = 0; i < npop; i++) {
            population[i] = q.front().get();
            q.pop();
        }
        addToQueueThread.join();

        return population;

    }

    Population Population::fromLHS(
            int npop, int nparams,
            const std::vector<double> &startingParam, std::vector<double> lb,
            std::vector<double> ub, bool logspace) {
        // just use other overload
        Population population = Population::fromLHS(npop, nparams, std::move(lb), std::move(ub), logspace);
        // and add individual
        population[0] = Individual(startingParam);
        return population;
    }

    double Population::evaluateMultiThreadedManual(CostFunction cost) {
        double total = 0;

        std::mutex mtx;
        std::vector<std::shared_future<double>> futures;
        auto compute1 = [&](int startIndex, int endIndex) {
            double sum = 0;
            for (int i = startIndex; i <= endIndex; i++) {
                std::lock_guard<std::mutex> lock(mtx);
                sum += contents_[i].evaluate(cost);
            }
            return sum;
        };

        // deal with situation where population size < hardware_concurrency.
        int numThreads = 0;
        if (size() < (int) std::thread::hardware_concurrency() - 1) {
            numThreads = size() - 1; // account for 0 index
        } else {
            numThreads = (int) std::thread::hardware_concurrency() - 1; // account for main thread
        }
        int numPerThread = floor(size() / numThreads);
        int remainder = size() % numThreads;

        int startIndex = 0;
        int endIndex = numPerThread;

        for (int i = 0; i < numThreads; i++) {
            if (i < remainder) {
                // we need to add one more job for these threads
                startIndex = i * (numPerThread + 1);
                endIndex = startIndex + numPerThread;
            } else {
                startIndex = i * numPerThread + remainder;
                endIndex = startIndex + (numPerThread - 1);
            }
            std::cout << "thread " << i << "; start index: " << startIndex << "; end index:  " << endIndex << std::endl;
            std::shared_future<double> f = std::async(std::launch::async, compute1, startIndex, endIndex);
            futures.push_back(f);
        }

        // now collect the results from futures
        for (auto &future : futures) {
            total += future.get();
        }
        return total;
    }

    double Population::evaluate(CostFunction cost) {
        double total = 0;
        std::for_each(std::execution::par, contents_.begin(), contents_.end(), [&](Individual& ind){
            total += ind.evaluate(cost);
        });
        return total;
    }


}
