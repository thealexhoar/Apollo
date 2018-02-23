/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <memory>
#include <unordered_map>

#include "entity.hpp"
#include "storage.hpp"
#include "types.hpp"

namespace apollo {
    //Worlds "create" ResourceAccessors, so best to forward declare here
   //class World;

    class ResourceAccessor {
        friend class World;

    private:
        //TODO 2/18/2018: Implement
        std::unordered_map<ComponentType, std::shared_ptr<void>> _storages;
        std::unordered_map<ResourceType, std::shared_ptr<void>> _resources;

    private:
        ResourceAccessor() :
            _storages(),
            _resources()
        {}


    public:

        ~ResourceAccessor() {

        }

        template <class C>
        const Storage<C>& read_storage() const {
            auto type = Types::component_type<C>();
            auto void_ptr = _storages[type];
            auto storage_ptr = std::static_pointer_cast<const Storage<C>>(void_ptr);
            return *storage_ptr;
        }

        template <class C>
        Storage<C>& get_storage() {
            auto type = Types::component_type<C>();
            auto void_ptr = _storages[type];
            auto storage_ptr = std::static_pointer_cast<Storage<C>>(void_ptr);
            return *storage_ptr;
        };

        template <class R>
        const R& read_resource() const {
            auto type = Types::resource_type<R>();
            auto void_ptr = _resources[type];
            auto resource_ptr = std::static_pointer_cast<const R>(void_ptr);
            return *resource_ptr;
        }

        template <class R>
        R& get_resource() {
            auto type = Types::resource_type<R>();
            auto void_ptr = _resources[type];
            auto resource_ptr = std::static_pointer_cast<R>(void_ptr);
            return *resource_ptr;
        }
        
    };

}