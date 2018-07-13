/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include "resource_accessor.hpp"
#include "resource_subscription.hpp"

namespace apollo {
    class ResourceAccessor;
    class World;

    class System {
        friend class World;

    private:
        ResourceSubscription resource_subscription_;

    public:
        System(ResourceSubscription resource_subscription) : resource_subscription_(resource_subscription) {}
        const ResourceSubscription& get_subscription() {
            return resource_subscription_;
        }
        virtual void update(ResourceAccessor& accessor) = 0;
    };

}