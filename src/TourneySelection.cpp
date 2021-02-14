
#include "TourneySelection.h"
#include "RandomNumberGenerator.h"
#include <thread>
#include <future>
#include <mutex>


namespace opt{

    std::vector<int> TourneySelection::select() {
        RandomNumberGenerator rng = RandomNumberGenerator::getInstance();
        std::vector<int> winners(k_);
        for (int i=0; i<k_; i++){
            auto contestants = rng.uniformIntWithoutReplacement(0, population_->size(), tournsize_);
            // now we figure out which is best
            int bestIndex = std::numeric_limits<int>::max();
            for (int contestant : contestants){
                const Individual& individual = (*population_)[contestant];
                if (individual.getFitness() < bestIndex){
                    bestIndex = contestant;
                }
            }
            winners[i] = bestIndex;
        }
        return winners;
    }

//    TourneySelection::TourneySelection(SharedPopulation population, int tournsize, int k)
//        : Selection(std::move(population)), tournsize_(tournsize), k_(k){}
}