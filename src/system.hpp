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

    public:
        System() {}
        virtual const ResourceSubscription& get_subscription() const = 0;
        virtual void update(ResourceAccessor& accessor) = 0;
    };

}