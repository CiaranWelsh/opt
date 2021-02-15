//
// Created by Ciaran on 13/02/2021.
//

#ifndef SRES_BLOCKINGQUEUE_H
#define SRES_BLOCKINGQUEUE_H

#include <queue>
#include <future>
#include <mutex>

template<class E>
class BlockingQueue {
public:
    explicit BlockingQueue(int maxSize) : maxSize_(maxSize) {};

    /**
     * Add element of type E to queue
     */
    void push(E e) {
        // you can only wait after we've got the lock, and we can only notify after we've
        // unlocked!
        std::unique_lock<std::mutex> lock(mtx_);
        // we return True in the predicate when we can stop waiting.
        conditionVariable_.wait(lock, [this]() { return que_.size() < maxSize_; });
        que_.push(e);
        lock.unlock();
        conditionVariable_.notify_one();
    };

    /**
     * get front of queue
     */
    E front() {
        std::unique_lock<std::mutex> lock(mtx_);
        conditionVariable_.wait(lock, [this]() { return !que_.empty(); });
        return que_.front();
    }

    /**
     * Remove element from queue
     */
    void pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        // wait is going to give up the lock temporarily
        conditionVariable_.wait(lock, [this]() { return !que_.empty(); });
        que_.pop();
        lock.unlock();
        conditionVariable_.notify_one();
    }

    int size() {
        std::lock_guard<std::mutex> lock(mtx_);
        return que_.size();
    }

    /**
     * @brief when distributing computation
     * using multithreading we evenly split the @param workLoad
     * into @param nThreads and handle the remainder
     */
    static void computeDistributedIndices(int nThreads, int workLoad) {
        // work out how many jobs per thread
        int jobsPerThread = floor(workLoad / nThreads);

        // check for remainder
        int r = workLoad % nThreads;

        // could offload this to a class
        // DistributedWorkloadSchedule
        //    -
    }

private:
    int maxSize_;
    std::queue<E> que_ {};
    std::mutex mtx_ {};
    std::condition_variable conditionVariable_{};
};


#endif //SRES_BLOCKINGQUEUE_H
