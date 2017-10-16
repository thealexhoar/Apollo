/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include "resource_accessor.hpp"
#include "resource_subscription.hpp"

namespace apollo {
    class World;

    class System {
        friend class World;
    protected:
        ResourceSubscription _subscription;

    public:
        System() : _subscription() {}
        System(const ResourceSubscription& subscription) : _subscription(subscription) {}
        virtual void update(ResourceAccessor& accessor) = 0;
    };

}