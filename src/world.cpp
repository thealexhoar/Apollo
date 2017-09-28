/*
CREATED: 16/09/17
NOTES: 
*/

#include "world.hpp"

namespace apollo {

    World::World() :
            _components(),
            _component_read_locks(),
            _component_write_locks(),
            _resources(),
            _resource_read_locks(),
            _resource_write_locks(),
            _type_manager()
    {}

    World::~World() {}

    ResourceAccessor* World::lock_for(const ResourceSubscription& resource_subscription) {
        ResourceAccessor* accessor = new ResourceAccessor(_type_manager);
        for (
                auto it = resource_subscription._read_components.begin();
                it != resource_subscription._read_components.end();
                it++
        ) {
            _component_read_locks[*it].lock();
            accessor->_read_components[*it] = _components[*it].get();
        }
        for (
                auto it = resource_subscription._write_components.begin();
                it != resource_subscription._write_components.end();
                it++
        ) {
            _component_read_locks[*it].lock();
            _component_write_locks[*it].lock();
            accessor->_write_components[*it] = _components[*it].get();
        }

        for (
                auto it = resource_subscription._read_resources.begin();
                it != resource_subscription._read_resources.end();
                it++
        ) {
            _resource_read_locks[*it].lock();
            accessor->_read_resources[*it] = _resources[*it].get();
        }

        for (
                auto it = resource_subscription._write_resources.begin();
                it != resource_subscription._write_resources.end();
                it++
        ) {
            _resource_read_locks[*it].lock();
            _resource_write_locks[*it].lock();
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
            _component_read_locks[it->first].unlock();
        }
        for (
                auto it = resource_accessor->_write_components.begin();
                it != resource_accessor->_write_components.end();
                it++
        ) {
            _component_read_locks[it->first].unlock();
            _component_write_locks[it->first].unlock();
        }

        for (
                auto it = resource_accessor->_read_resources.begin();
                it != resource_accessor->_read_resources.end();
                it++
        ) {
            _resource_read_locks[it->first].unlock();
        }

        for (
                auto it = resource_accessor->_write_resources.begin();
                it != resource_accessor->_write_resources.end();
                it++
        ) {
            _resource_read_locks[it->first].unlock();
            _resource_write_locks[it->first].unlock();
        }
    }

    template <class T>
    bool World::register_component() {
        ComponentType type = _type_manager.get_component_type<T>();
        if (_components.count(type) > 0) {
            return false;
        }
        else {
            _components[type] = std::unique_ptr<ComponentArray>(ComponentArray::new_for_type<T>(INITIAL_CAPACITY));
            _component_read_locks.emplace(type);
            _component_write_locks.emplace(type);
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
            return true;
        }
    }
}

