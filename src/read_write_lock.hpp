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
        uint32_t _count, _initial_count;
        std::condition_variable _cv;
        std::mutex _semaphore_mutex, _write_mutex;

    public:
        ReadWriteLock(uint32_t initial_count = 1) :
                _count(initial_count),
                _initial_count(initial_count),
                _cv(),
                _semaphore_mutex(),
                _write_mutex()
        {}

        void lock_for_read() {
            wait(1);
        }

        void lock_for_write() {
            std::unique_lock<decltype(_write_mutex)> lock(_write_mutex);
            for(int i = 0; i < _initial_count; i++) {
                wait(1);
            }
        }

        void unlock_for_read() {
            notify(1);
        }

        void unlock_for_write() {
            notify(_initial_count);
        }

    private:
        void notify(uint32_t count = 1) {
            std::unique_lock<decltype(_semaphore_mutex)> lock(_semaphore_mutex);
            _count += count;
            _cv.notify_one();
        }

        void wait(uint32_t count = 1) {
            std::unique_lock<decltype(_semaphore_mutex)> lock(_semaphore_mutex);
            while(_count < count) {
                _cv.wait(lock);
            }
            _count -= count;
        }
    };
}
