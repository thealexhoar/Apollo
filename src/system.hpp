/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include "resource_accessor.hpp"
#include "resource_subscription.hpp"

namespace apollo {

    class System {
    private:
        ResourceSubscription _subscription;

    public:
        System(const ResourceSubscription& subscription);
        virtual ~System() = 0;

        virtual void update(ResourceAccessor& accessor) = 0;

    };

}