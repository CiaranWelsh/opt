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

namespace opt {

    Population::Population(int npop, int nparam) {
        std::vector<Individual> ind(npop);
        for (int i = 0; i < npop; i++) {
            ind[i] = Individual(nparam);
        }
        contents_ = ind;
    };

    Population::Population(std::vector<std::vector<double>> input) {
        std::vector<Individual> ind;
        for (auto &it: input) {
            contents_.emplace_back(it);
        }

    }

    Population::Population(std::initializer_list<std::initializer_list<double>>
    input) {
    std::vector<Individual> ind;
    for (
    auto &it
    : input) {
    contents_.
    emplace_back(it);
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

}
