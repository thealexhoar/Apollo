/*
CREATED: 16/09/17
NOTES: 
*/

#include <memory>

#include "storage.hpp"
#include "world.hpp"

namespace apollo {

    World::World() : World(1024) {}

    World::World(size_t initial_component_capacity) :
        resources_(),
        storages_()
    {}


    World::~World() {}

    ResourceAccessor World::give_access(const ResourceSubscription &resource_subscription) {
        ResourceAccessor accessor;

        for (const auto& c_type : resource_subscription.read_components_) {
            if (storages_.count(c_type) == 0) {
                return accessor;
            }

            accessor.read_storages_[c_type] = storages_[c_type];
        }

        for (const auto& c_type : resource_subscription.write_components_) {
            if (storages_.count(c_type) == 0) {
                return accessor;
            }

            if (accessor.read_storages_.count(c_type) > 0) {
                accessor.read_storages_.erase(c_type);
            }

            accessor.write_storages_[c_type] = storages_[c_type];
        }

        for (const auto& r_type : resource_subscription.read_resources_) {
            if (resources_.count(r_type) == 0) {
                return accessor;
            }

            accessor.read_resources_[r_type] = resources_[r_type];
        }

        for (const auto& r_type : resource_subscription.write_resources_) {
            if (resources_.count(r_type) == 0) {
                return accessor;
            }

            if (accessor.read_resources_.count(r_type) > 0) {
                accessor.read_resources_.erase(r_type);
            }

            accessor.write_resources_[r_type] = resources_[r_type];
        }

        return accessor;
    }



}

