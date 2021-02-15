
#include "TourneySelection.h"
#include "RandomNumberGenerator.h"
#include <thread>
#include <future>
#include <mutex>


namespace opt{
    TourneySelection::TourneySelection(SharedPopulation population, int tournsize, int howMany)
        : Selection(std::move(population), howMany), tournsize_(tournsize){}

    void TourneySelection::select() {
        RandomNumberGenerator rng = RandomNumberGenerator::getInstance();

        std::vector<int> selection(howMany_);
        for (int i=0; i<howMany_; i++){
            auto contestants = rng.uniformIntWithoutReplacement(0, population_->size(), tournsize_);
            // now we figure out which is best
            int bestIndex = std::numeric_limits<int>::max();
            for (int contestant : contestants){
                const Individual& individual = (*population_)[contestant];
                if (individual.getFitness() < bestIndex || bestIndex == std::numeric_limits<int>::max()){
                    bestIndex = contestant;
                }
            }
            selection[i] = bestIndex;
        }

        // sort the first k items based on fitness, then don't bother with extra complexity.
        std::partial_sort(population_->begin(), population_->begin() + howMany_, population_->end(),
                          [&](Individual& ind1, Individual& ind2){
            return ind1.getFitness()< ind2.getFitness();
        });

        // resize to howMany_ individuals, which contains the top `howMany_`
        population_->resize(howMany_);

    }

    TourneySelection::TourneySelection(int tournsize, int howMany, int numEstimatedParams)
        : Selection(howMany, numEstimatedParams), tournsize_(tournsize){}

}