#include <chrono>
#include <random>
#include <iostream>
#include <thread>
#include <future>
#include <execution>
#include <mutex>
#include <vector>
#include <array>


double BealeFunction(double *parameters) {
    double x = parameters[0];
    double y = parameters[1];
    double first = pow(1.5 - x + x * y, 2);
    double second = pow(2.25 - x + x * pow(y, 2), 2);
    double third = pow(2.625 - x + x * pow(y, 3), 2);
    return first + second + third;
};

double inSerial(std::vector<std::array<double, 2>> matrix){
    double total = 0;
    for (auto & i : matrix){
        total += BealeFunction(i.data());
    }
    return total;
}

double usingExecution(std::vector<std::array<double, 2>> matrix){
    double total = 0;
    std::for_each(std::execution::unseq, matrix.begin(), matrix.end(), [&](std::array<double, 2>& ind){
        total += BealeFunction(ind.data());
    });
    return total;
}

double withThreading(std::vector<std::array<double, 2>> matrix){
    double total = 0;
    std::mutex mtx;
    std::vector<std::shared_future<double>> futures;

    auto compute1 = [&](int startIndex, int endIndex) {
        double sum = 0;
        for (int i = startIndex; i <= endIndex; i++) {
            sum += BealeFunction(matrix[i].data());
        }
        return sum;
    };

    // deal with situation where population size < hardware_concurrency.
    int numThreads = 0;
    if (matrix.size() < (int) std::thread::hardware_concurrency() - 1) {
        numThreads = matrix.size() - 1; // account for 0 index
    } else {
        numThreads = (int) std::thread::hardware_concurrency() - 1; // account for main thread
    }
    int numPerThread = floor(matrix.size() / numThreads);
    int remainder = matrix.size() % numThreads;

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

int main() {
    auto start = std::chrono::steady_clock::now();

    int N = 1e7;
    int M = 2;

    // (setup code)
    std::vector<std::array<double, 2>> matrix(N, std::array<double, 2>());
    int seed = 5;
    std::default_random_engine e(seed);
    std::uniform_real_distribution<double> dist1(2.9, 3.1);
    std::uniform_real_distribution<double> dist2(0.4, 0.6);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][0] = dist1(e);
            matrix[i][1] = dist2(e);
        }
    }

//    double total = withThreading(matrix);
//    double total = inSerial(matrix);
    double total = usingExecution(matrix);


    auto end = std::chrono::steady_clock::now();
    std::cout << "fitness: " << total << std::endl;
    std::cout << "computation took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " microseonds" << std::endl;


    /**
     * Results
     * -------
     *
     * In serial: fitness = 829459; computation took:      9565702 microseonds vs 5717079 with array
     * In serial: fitness = 829459; computation took:      9388721 microseonds vs 5672010 with array
     *
     * With threading: fitness = 829459; computation took: 7161206 microseonds vs 3616953 with array
     * With threading: fitness = 829459; computation took: 7057340 microseonds vs 3653799 with array
     *
     *
     * With execution: fitness = 829459; computation took: 7057340 microseonds vs 3627365 with array
     *
     */


}










