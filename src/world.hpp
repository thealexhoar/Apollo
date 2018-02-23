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
    static constexpr const uint32_t MAX_PARALLEL_READERS = 32;

    class ResourceAccessor;

    class World {
    private:
        std::unordered_map<ComponentType, std::shared_ptr<void>> _storages;
        std::unordered_map<ResourceType, std::shared_ptr<void>> _resources;

        ResourceAccessor _all_resources;

    public:
        World();
        ~World();

        ResourceAccessor& all_resources();

        std::unique_ptr<ResourceAccessor> lock_for(const ResourceSubscription& resource_subscription);

        template <class C, class S>
        bool register_component();

        template <class R>
        bool register_resource(const R& initial_value);
    };

}
