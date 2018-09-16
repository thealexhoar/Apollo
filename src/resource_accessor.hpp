/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <memory>
#include <iostream>
#include <unordered_map>

#include "entity.hpp"
#include "storage.hpp"
#include "types.hpp"
#include "world.hpp"

namespace apollo {
    //Worlds "create" ResourceAccessors, so best to forward declare here
    class World;

    class ResourceAccessor {
        friend class World;

    private:
        //TODO 2/18/2018: Implement
        std::unordered_map<ResourceType, std::weak_ptr<void const>> read_resources_;
        std::unordered_map<ComponentType, std::weak_ptr<void const>> read_storages_;
        std::unordered_map<ResourceType, std::weak_ptr<void>> write_resources_;
        std::unordered_map<ComponentType, std::weak_ptr<void>> write_storages_;

    private:
        ResourceAccessor() :
                read_resources_(),
                read_storages_(),
                write_resources_(),
                write_storages_()
        {}

    public:

        template <class C>
        const Storage<C>& read_storage() const {
            auto type = Types::component_type<C>();
            auto void_ptr = read_storages_[type].lock();
            auto storage_ptr = std::static_pointer_cast<const Storage<C>>(void_ptr);
            return *storage_ptr;
        }

        template <class C>
        Storage<C>& write_storage() {
            auto type = Types::component_type<C>();
            auto void_ptr = write_storages_[type].lock();
            auto storage_ptr = std::static_pointer_cast<Storage<C>>(void_ptr);
            return *storage_ptr;
        };

        template <class R>
        const R& read_resource() const {
            auto type = Types::resource_type<R>();
            auto void_ptr = write_resources_[type].lock();
            auto resource_ptr = std::static_pointer_cast<const R>(void_ptr);
            return *resource_ptr;
        }

        template <class R>
        R& write_resource() {
            auto type = Types::resource_type<R>();
            auto void_ptr = write_resources_[type].lock();
            auto resource_ptr = std::static_pointer_cast<R>(void_ptr);
            return *resource_ptr;
        }
    };

}