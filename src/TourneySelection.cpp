
#include "TourneySelection.h"
#include "RandomNumberGenerator.h"
#include <thread>
#include <future>
#include <mutex>


namespace opt{
    TourneySelection::TourneySelection(SharedPopulation population, int tournsize, int k)
        : Selection(std::move(population)), tournsize_(tournsize), k_(k){}

    void TourneySelection::select(SharedPopulation &nextGen) {
        RandomNumberGenerator rng = RandomNumberGenerator::getInstance();
        for (int i=0; i<k_; i++){
            auto contestants = rng.uniformIntWithoutReplacement(0, population_->size(), tournsize_);
            // now we figure out which is best
            int bestIndex = std::numeric_limits<int>::max();
            for (int contestant : contestants){
                const Individual& individual = (*population_)[contestant];
                if (individual.getFitness() < bestIndex || bestIndex == std::numeric_limits<int>::max()){
                    bestIndex = contestant;
                }
            }
            (*nextGen)[i] = (*population_)[bestIndex];
        }
    }

    TourneySelection::TourneySelection(int tournsize, int k)
        : tournsize_(tournsize), k_(k){}


}