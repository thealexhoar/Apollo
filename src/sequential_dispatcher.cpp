//
// Created by alex on 23/01/18.
//

#include "sequential_dispatcher.hpp"

namespace apollo {
    template <class T>
    SequentialDispatcher<T>::SequentialDispatcher() : _systems() {}


    template <class T>
    void SequentialDispatcher<T>::dispatch(World &world) {
        for (auto i = 0; i < _systems.size(); i++) {
            _systems[i]->update(world.all_resources());
        }
    }

    template <class T>
    SequentialDispatcherBuilder<T>::SequentialDispatcherBuilder() :
            _systems(),
            _topology()
    {}

    template <class T>
    void SequentialDispatcherBuilder<T>::add_system(
        std::shared_ptr<System> system,
        T ID,
        std::vector<T> dependencies
    ) {
        _systems.insert(ID, system);
        _topology.insert(ID, dependencies);
    }

    template <class T>
    SequentialDispatcher<T> SequentialDispatcherBuilder<T>::build(){
        auto sequential_dispatcher = SequentialDispatcher<T>();

        auto temp_topology = _topology;
        auto sorted_IDs = std::vector<T>();
        auto independent_set = std::vector<T>();

        for (
            auto iterator = temp_topology.begin();
            iterator != temp_topology.end();
            iterator++
        ) {
            if (iterator->second.size() == 0) {
                independent_set.push_back(iterator->first);
            }
        }

        while (independent_set.size() > 0) {
            auto ID = independent_set[independent_set.size() - 1];
            independent_set.pop_back();
            sorted_IDs.push_back(ID);

            for (
                auto iterator = temp_topology.begin();
                iterator != temp_topology.end();
                iterator++
            ) {
                std::vector<T>& topology = iterator->second;
                for (auto i = topology.size()-1; i >= 0; i--) {
                    if (topology[i] == ID) {
                        topology.erase(topology.begin()+i);
                    }
                }
                if (topology.size() == 0) {
                    independent_set.push_back(iterator->first);
                }
            }

            for (int i = 0; i < independent_set.size(); i++) {
                auto id = independent_set[i];
                if(temp_topology.count(id) > 0) {
                    temp_topology.erase(id);
                }
            }
        }

        for (auto i = 0; i < sorted_IDs.size(); i++) {
            auto system = _systems[sorted_IDs[i]];
            sequential_dispatcher._systems.push_back(system);
        }

        return sequential_dispatcher;
    }
}