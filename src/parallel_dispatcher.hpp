//
// Created by alex on 23/01/18.
//

#pragma once

#include <map>
#include <memory>

#include "dispatcher.hpp"
#include "system.hpp"


namespace apollo {
    template<class T>
    class ParallelDispatcher : public Dispatcher {
        friend class ParallelDispatcherBuilder;
    private:
        std::map<T, std::shared_ptr<System>> _systems;
    public:
        ~ParallelDispatcher();

        void dispatch(World& world) override;
    private:
        ParallelDispatcher();

    };

    template<class T>
    class ParallelDispatcherBuilder {
    public:
        ParallelDispatcherBuilder();

        ParallelDispatcher<T> build();
    };
}