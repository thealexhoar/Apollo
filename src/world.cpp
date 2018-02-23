/*
CREATED: 16/09/17
NOTES: 
*/

#include "world.hpp"

namespace apollo {

    World::World() :
        _storages(),
        _resources(),
        _all_resources()
    {}

    World::~World() {}

    ResourceAccessor& World::all_resources() {
        return _all_resources;
    }

    ResourceAccessor* World::lock_for(const ResourceSubscription& resource_subscription) {
        // TODO 2/18/2018: implement
    }

    void World::unlock_for(ResourceAccessor* resource_accessor) {
        // TODO 2/18/2018: implement
    }

    template <class T>
    bool World::register_component() {
        // TODO 2/18/2018: implement
    }

    template <class T>
    bool World::register_resource(const T& initial_value) {
        // TODO 2/18/2018: implement
    }
}

