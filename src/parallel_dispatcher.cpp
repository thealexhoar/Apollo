//
// Created by alex on 23/01/18.
//

#include "parallel_dispatcher.hpp"

namespace apollo {
    template <class T>
    ParallelDispatcher<T>::ParallelDispatcher() {}

    template <class T>
    ParallelDispatcher<T>::~ParallelDispatcher() {}

    template <class T>
    void ParallelDispatcher<T>::dispatch(World &world) {}

    template <class T>
    ParallelDispatcherBuilder<T>::ParallelDispatcherBuilder() {}

    template <class T>
    ParallelDispatcher<T> ParallelDispatcherBuilder<T>::build() {
        return ParallelDispatcher<T>();
    }
}