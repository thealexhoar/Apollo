/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include <memory>
#include <mutex>

#include "resource_accessor.hpp"
#include "resource_subscription.hpp"
#include "resource_wrapper.hpp"



namespace apollo {

    static constexpr const size_t INITIAL_CAPACITY = 1024;

    class ResourceAccessor;

    class World {
    private:
        std::unordered_map<ComponentType, std::unique_ptr<ComponentArray>> _components;
        std::unordered_map<ComponentType, std::mutex> _component_read_locks, _component_write_locks;
        std::unordered_map<ResourceType, std::unique_ptr<ResourceWrapper>> _resources;
        std::unordered_map<ResourceType, std::mutex> _resource_read_locks, _resource_write_locks;

        TypeManager _type_manager;

    public:
        World();
        ~World();

        ResourceAccessor* lock_for(const ResourceSubscription& resource_subscription);

        void unlock_for(ResourceAccessor* resource_accessor);

        template <class T>
        bool register_component();

        template <class T>
        bool register_resource(const T& initial_value);
    };

}
