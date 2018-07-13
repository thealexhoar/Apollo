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
        mutex_(),
        resources_(),
        storages_(),
        resource_locks_(),
        storage_locks_()
    {}

    World::World(const World& other) :
        mutex_(),
        resources_(other.resources_),
        storages_(other.storages_),
        resource_locks_(other.resource_locks_),
        storage_locks_(other.storage_locks_)
    {}

    World::~World() {}

    std::unique_ptr<ResourceAccessor> World::lock_for(const ResourceSubscription& resource_subscription) {
        std::unique_lock<decltype(mutex_)> lock(mutex_); //prevent deadlock within this function
        auto accessor = std::unique_ptr<ResourceAccessor>(new ResourceAccessor(*this));

        for (const auto& c_type : resource_subscription.read_components_) {
            if (storages_.count(c_type) == 0) {
                accessor.reset();
                return accessor;
            }

            storage_locks_[c_type].lock_for_read();
            accessor->read_storages_[c_type] = std::weak_ptr<const void>(storages_[c_type]);
        }

        for (const auto& c_type : resource_subscription.write_components_) {
            if (storages_.count(c_type) == 0) {
                accessor.reset();
                return accessor;
            }

            if (accessor->read_storages_.count(c_type) > 0) {
                accessor->read_storages_.erase(c_type);
                storage_locks_[c_type].release_from_read();
            }
            storage_locks_[c_type].lock_for_write();
            accessor->write_storages_[c_type] = std::weak_ptr<void>(storages_[c_type]);
        }

        for (const auto& r_type : resource_subscription.read_resources_) {
            if (resources_.count(r_type) == 0) {
                accessor.reset();
                return accessor;
            }

            resource_locks_[r_type].lock_for_read();
            accessor->read_resources_[r_type] = std::weak_ptr<const void>(resources_[r_type]);
        }

        for (const auto& r_type : resource_subscription.write_resources_) {
            if (resources_.count(r_type) == 0) {
                accessor.reset();
                return accessor;
            }

            if (accessor->read_resources_.count(r_type) > 0) {
                accessor->read_resources_.erase(r_type);
                resource_locks_[r_type].release_from_read();
            }
            resource_locks_[r_type].lock_for_write();
            accessor->write_resources_[r_type] = std::weak_ptr<void>(resources_[r_type]);
        }

        return accessor;
    }

    template <class C, class S>
    bool World::register_component() {
        static_assert(std::is_base_of<Storage<C>, S>().value);

        auto type = Types::component_type<C>();
        if(storages_.count(type) > 0) {
            return false;
        }
        else {
            storages_[type] = std::make_shared<S>();
            storage_locks_[type] = ReadWriteLock();
            return true;
        }
    }

    template <class R>
    bool World::register_resource(const R& initial_value) {
        auto type = Types::resource_type<R>();
        if(resources_.count(type) > 0) {
            return false;
        }
        else {
            resources_[type] = std::make_shared<R>();
            resource_locks_[type] = ReadWriteLock();
            return true;
        }
    }
}

