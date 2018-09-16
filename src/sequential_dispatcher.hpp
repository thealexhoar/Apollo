//
// Created by alex on 23/01/18.
//

#pragma once

#include <map>
#include <memory>
#include <vector>

#include "dispatcher.hpp"
#include "system.hpp"
#include "world.hpp"

namespace apollo {
    class SequentialDispatcher : public Dispatcher {
    private:
        std::vector<std::shared_ptr<System>> systems_;

    public:
        SequentialDispatcher(std::vector<std::shared_ptr<System>>&& systems) : systems_(systems) {}
        void dispatch(World& world) override;

    };

    template<class T>
    class SequentialDispatcherBuilder {
    private:
        std::map<T, std::shared_ptr<System>> systems_;
        std::map<T, std::vector<T>> topology_;
    public:
        SequentialDispatcherBuilder();

        void add_system(
                std::shared_ptr<System> system,
                T ID,
                std::vector<T> dependencies
        );
        SequentialDispatcher build();
    };
}