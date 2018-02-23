/*
CREATED: 16/09/17
NOTES: 
*/

#include <memory>

#include "storage.hpp"
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

    std::unique_ptr<ResourceAccessor> World::lock_for(const ResourceSubscription& resource_subscription) {
        // TODO 2/18/2018: implement
        return std::unique_ptr<ResourceAccessor>();
    }

    template <class C, class S>
    bool World::register_component() {
        static_assert(std::is_base_of<Storage<C>, S>().value);
        auto type = Types::component_type<C>();
        if(_storages.count(type) > 0) {
            return false;
        }
        else {
            _storages[type] = std::make_shared<S>();
            return true;
        }
    }

    template <class R>
    bool World::register_resource(const R& initial_value) {
        // TODO 2/18/2018: implement
    }
}

