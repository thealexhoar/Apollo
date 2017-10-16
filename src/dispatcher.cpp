/*
CREATED: 27/09/17
NOTES: 
*/

#include "dispatcher.hpp"

namespace apollo {
    template <class T>
    Dispatcher<T>::Dispatcher() :
        _sorted_systems(),
        _stages()
    {

    }

    template <class T>
    void Dispatcher<T>::dispatch_parallel(World& world) {

    }

    template <class T>
    void Dispatcher<T>::dispatch_sequential(World& world) {
        auto& accessor = world.all_resources();
        for (auto i = 0; i < _sorted_systems.size(); i++) {
            _sorted_systems[i]->update(accessor);
        }
    }


    template <class T>
    DispatcherBuilder<T>::DispatcherBuilder() :
            _last_system(),
            _last_system_set(false),
            _systems(),
            _topology()
    {}

    template <class T>
    DispatcherBuilder<T>& DispatcherBuilder<T>::add_system(System* system, const T& name) {
        if(_systems.count(name) == 0) {
            _last_system = name;
            _last_system_set = true;
            _systems.insert(name, system);
            _topology.insert(name, std::vector<T>());
        }
        return *this;
    }

    template <class T>
    DispatcherBuilder<T>& DispatcherBuilder<T>::after(const T& name) {
        if(_last_system_set) {
            _topology[_last_system].push_back(name);
        }
        return *this;
    }

    template <class T>
    Dispatcher<T> DispatcherBuilder<T>::build() {

    }
}