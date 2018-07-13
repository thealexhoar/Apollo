/*
CREATED: 02/10/17
NOTES: 
*/

#pragma once

#include <cinttypes>
#include <condition_variable>
#include <mutex>

namespace apollo {
    class ReadWriteLock {
    private:
        std::condition_variable cv_;
        std::mutex mutex_;
        uint32_t waiting_reads_;
        bool waiting_write_;

    public:
        ReadWriteLock() :
            cv_(),
            mutex_(),
            waiting_reads_(0),
            waiting_write_(false)
        {}

        ReadWriteLock(const ReadWriteLock& other) : ReadWriteLock() {}

        void lock_for_read() {
            std::unique_lock<decltype(mutex_)> lock(mutex_);
            while (waiting_write_) {
                cv_.wait(lock);
            }
            waiting_reads_++;
        }

        void lock_for_write() {
            std::unique_lock<decltype(mutex_)> lock(mutex_);
            while (waiting_write_ || waiting_reads_ > 0) {
                cv_.wait(lock);
            }
            waiting_write_ = true;
        }

        void release_from_read() {
            std::unique_lock<decltype(mutex_)> lock(mutex_);
            waiting_reads_--;
            if (waiting_reads_ == 0) {
                cv_.notify_one();
            }
        }

        void release_from_write() {
            std::unique_lock<decltype(mutex_)> lock(mutex_);
            waiting_write_ = false;
            cv_.notify_all();
        }
    };
}
