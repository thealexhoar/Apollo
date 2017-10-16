/*
CREATED: 16/09/17
NOTES: 
*/

#include "world.hpp"

namespace apollo {

        World::World() :
            _components(),
            _component_locks(),
            _resources(),
            _resource_locks(),
            _type_manager(),
            _all_resources(_type_manager)
    {}

    World::~World() {}

    ResourceAccessor& World::all_resources() {
        return _all_resources;
    }

    ResourceAccessor* World::lock_for(const ResourceSubscription& resource_subscription) {
        ResourceAccessor* accessor = new ResourceAccessor(_type_manager);
        for (
                auto it = resource_subscription._read_components.begin();
                it != resource_subscription._read_components.end();
                it++
        ) {
            _component_locks[*it].lock_for_read();
            accessor->_read_components[*it] = _components[*it].get();
        }
        for (
                auto it = resource_subscription._write_components.begin();
                it != resource_subscription._write_components.end();
                it++
        ) {
            _component_locks[*it].lock_for_write();
            accessor->_write_components[*it] = _components[*it].get();
        }

        for (
                auto it = resource_subscription._read_resources.begin();
                it != resource_subscription._read_resources.end();
                it++
        ) {
            _resource_locks[*it].lock_for_read();
            accessor->_read_resources[*it] = _resources[*it].get();
        }

        for (
                auto it = resource_subscription._write_resources.begin();
                it != resource_subscription._write_resources.end();
                it++
        ) {
            _resource_locks[*it].lock_for_write();

            accessor->_write_resources[*it] = _resources[*it].get();
        }

        return accessor;
    }

    void World::unlock_for(ResourceAccessor* resource_accessor) {
        for (
                auto it = resource_accessor->_read_components.begin();
                it != resource_accessor->_read_components.end();
                it++
        ) {
            _component_locks[it->first].unlock_for_read();
        }
        for (
                auto it = resource_accessor->_write_components.begin();
                it != resource_accessor->_write_components.end();
                it++
        ) {
            _component_locks[it->first].unlock_for_write();
        }

        for (
                auto it = resource_accessor->_read_resources.begin();
                it != resource_accessor->_read_resources.end();
                it++
        ) {
            _resource_locks[it->first].unlock_for_read();
        }

        for (
                auto it = resource_accessor->_write_resources.begin();
                it != resource_accessor->_write_resources.end();
                it++
        ) {
            _resource_locks[it->first].unlock_for_write();
        }
    }

    template <class T>
    bool World::register_component() {
        ComponentType type = _type_manager.get_component_type<T>();
        if (_components.count(type) > 0) {
            return false;
        }
        else {
            _components[type] = std::unique_ptr<ComponentArray>(ComponentArray::new_for_type<T>(INITIAL_COMPONENT_CAPACITY));
            _component_locks.emplace(type, MAX_PARALLEL_READERS);
            _all_resources._write_components.insert({type, _components[type].get()});
            return true;
        }
    }

    template <class T>
    bool World::register_resource(const T& initial_value) {
        ResourceType type = _type_manager.get_resource_type<T>();
        if (_resources.count(type) > 0) {
            return false;
        }
        else {
            _resources[type] = std::unique_ptr<ResourceWrapper>(ResourceWrapper::new_for_type<T>(initial_value));
            _resource_locks.emplace(type, MAX_PARALLEL_READERS);
            _all_resources._write_resources.insert({type, _resources[type].get()});
            return true;
        }
    }
}

