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

    public:
        const ResourceSubscription resource_subscription;

    public:
        System(ResourceSubscription resource_subscription) : resource_subscription(resource_subscription) {}

        virtual void update(ResourceAccessor& accessor) = 0;
    };

}