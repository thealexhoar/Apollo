/*
CREATED: 27/09/17
NOTES: 
*/

#include "dispatcher.hpp"

namespace apollo {
    template <class T>
    Dispatcher<T>::Dispatcher(bool async) :
            _async(async)
    {

    }

    template <class T>
    void Dispatcher<T>::dispatch(World& world) {

    }


    template <class T>
    DispatcherBuilder<T>::DispatcherBuilder() :
            _last_system(NULL),
            _systems(),
            _topology()
    {}

    template <class T>
    DispatcherBuilder<T>& DispatcherBuilder<T>::add_system(System* system, const T& name) {
        if(_systems.count(name) == 0) {
            _last_system = name;
            _systems.insert(name, system);
            _topology.insert(name, std::vector<T>());
        }
        return *this;
    }

    template <class T>
    DispatcherBuilder<T>& DispatcherBuilder<T>::after(const T& name) {
        if(_last_system != NULL) {
            _topology[_last_system].push_back(name);
        }
        return *this;
    }

    template <class T>
    Dispatcher<T> DispatcherBuilder<T>::build(bool async) {

    }
}