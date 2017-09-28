/*
CREATED: 26/09/17
NOTES: 
*/

#pragma once

#include <map>
#include <set>
#include <vector>

#include "system.hpp"

namespace apollo {
    template <class T>
    class DispatcherBuilder;

    template <class T>
    class Dispatcher {
        friend class DispatcherBuilder<T>;
    private:
        bool _async;

        Dispatcher(bool async);
    public:
        void dispatch(World& world);
    };

    template <class T>
    class DispatcherBuilder {
    private:
        T _last_system;
        std::map<T, System*> _systems;
        std::map<T, std::vector<T>> _topology;

    public:
        DispatcherBuilder();

        DispatcherBuilder<T>& add_system(System* system, const T& name);

        DispatcherBuilder<T>& after(const T& name);

        Dispatcher<T> build(bool async);
    };

}