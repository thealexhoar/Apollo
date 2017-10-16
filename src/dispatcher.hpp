/*
CREATED: 26/09/17
NOTES: 
*/

#pragma once

#include <map>
#include <set>
#include <vector>

#include "system.hpp"
#include "world.hpp"

namespace apollo {
    template <class T>
    class DispatcherBuilder;

    template <class T>
    class Dispatcher {
        friend class DispatcherBuilder<T>;
    private:
        std::vector<System*> _sorted_systems;
        std::vector<uint32_t> _stages;

        Dispatcher();

    public:
        void dispatch_parallel(World& world);
        void dispatch_sequential(World& world);
    };

    template <class T>
    class DispatcherBuilder {
    private:
        T _last_system;
        bool _last_system_set;
        std::map<T, System*> _systems;
        std::map<T, std::vector<T>> _topology;

    public:
        DispatcherBuilder();

        DispatcherBuilder<T>& add_system(System* system, const T& name);

        DispatcherBuilder<T>& after(const T& name);

        Dispatcher<T> build();
    };

}