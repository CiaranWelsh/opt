#include <chrono>
#include <random>
#include <iostream>

class RandomNumberGenerator {

public:

    static RandomNumberGenerator &getInstance(unsigned long long seed = 0) {
        if (seed == 0){
            seed = std::chrono::system_clock::now().time_since_epoch().count();
        }
        static RandomNumberGenerator singleton(seed);
        return singleton;
    }

    int uniformInt(int lb, int ub) {
        std::uniform_real_distribution<double> distibution(lb, ub);
        return distibution(generator_);
    }


    unsigned long long int getSeed() const {
        return seed_;
    }

    void setSeed(unsigned long long int seed) {
        seed_ = seed;
    }

    const std::default_random_engine &getGenerator() const {
        return generator_;
    }

    void setGenerator(const std::default_random_engine &generator) {
        generator_ = generator;
    }

public:

    explicit RandomNumberGenerator(
            unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count()
    ) : seed_(seed), generator_(std::default_random_engine(seed)) {}

    /**
     * @brief seed defaults to the current time
     * set by a high resolution clock. This c
     * can be set by the user to have predictable
     * random numbers
     */
    unsigned long long seed_;

    std::default_random_engine generator_;

};


int main() {

    RandomNumberGenerator rng = RandomNumberGenerator::getInstance(5);
    std::cout << &rng.generator_ << std::endl;
    std::cout << rng.getSeed() << std::endl;
    std::cout << rng.uniformInt(0, 10) << std::endl;



    RandomNumberGenerator rng2 = RandomNumberGenerator::getInstance();
    std::cout << &rng.generator_ << std::endl;
    std::cout << rng2.uniformInt(0, 25) << std::endl;

}










