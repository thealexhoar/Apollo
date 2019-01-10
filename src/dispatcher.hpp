//
// Created by alex on 23/01/18.
//

#pragma once

#include <map>
#include <memory>
#include <vector>

#include "system.hpp"
#include "world.hpp"

namespace apollo {
    class Dispatcher {
    private:
        std::vector<std::shared_ptr<System>> systems_;

    public:
        Dispatcher(std::vector<std::shared_ptr<System>>&& systems) : systems_(systems) {}
        void dispatch(World &world)  {
            for (auto& system: systems_) {
                system->update(world);
            }
        }

    };

    template<class T>
    class DispatcherBuilder {
    private:
        std::map<T, std::shared_ptr<System>> systems_;
        std::map<T, std::vector<T>> topology_;
    public:
        DispatcherBuilder() :
            systems_(),
            topology_()
        {}

        DispatcherBuilder& with_system(
            std::shared_ptr<System> system,
            T ID,
            std::vector<T> dependencies
        ) {
            add_system(system, ID, dependencies);
            return *this;
        }

        void add_system(
            std::shared_ptr<System> system,
            T ID,
            std::vector<T> dependencies
        ) {
            systems_.insert(ID, system);
            topology_.insert(ID, dependencies);
        }

        Dispatcher build() {

            auto temp_topology = topology_;
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
            std::vector<std::shared_ptr<System>> systems;
            for (auto i = 0; i < sorted_IDs.size(); i++) {
                auto system = systems_[sorted_IDs[i]];
                systems.push_back(system);
            }

            return Dispatcher(std::move(systems));
        }
    };
}