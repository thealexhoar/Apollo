/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include <memory>
#include <mutex>

#include "resource_accessor.hpp"
#include "resource_subscription.hpp"
#include "read_write_lock.hpp"
#include "types.hpp"

namespace apollo {

    static constexpr const size_t INITIAL_COMPONENT_CAPACITY = 1024;

    class ResourceAccessor;

    class World {
        friend class ResourceAccessor;
    private:
        std::mutex mutex_;
        std::unordered_map<ResourceType, std::shared_ptr<void>> resources_;
        std::unordered_map<ComponentType, std::shared_ptr<void>> storages_;
        std::unordered_map<ResourceType, ReadWriteLock> resource_locks_;
        std::unordered_map<ComponentType, ReadWriteLock> storage_locks_;


    public:
        World();
        World(size_t initial_component_capacity);
        World(const World& other);
        ~World();

        std::unique_ptr<ResourceAccessor> lock_for(const ResourceSubscription& resource_subscription);

        template <class C, class S>
        bool register_component();

        template <class R>
        bool register_resource(const R& initial_value);
    };

}
