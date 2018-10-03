/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include <memory>

#include "resource_accessor.hpp"
#include "resource_subscription.hpp"
#include "types.hpp"

namespace apollo {

    static constexpr const size_t INITIAL_COMPONENT_CAPACITY = 1024;

    class World {
    private:
        std::unordered_map<ResourceType, std::shared_ptr<void>> resources_;
        std::unordered_map<ComponentType, std::shared_ptr<void>> storages_;


    public:
        World();
        World(size_t initial_component_capacity);
        ~World();

        ResourceAccessor give_access(const ResourceSubscription &resource_subscription);

        template <class C, class S>
        bool register_component() {
            static_assert(std::is_base_of<Storage<C>, S>().value, "Type S must be a Storage for C!");

            auto type = Types::component_type<C>();
            if(storages_.count(type) > 0) {
                return false;
            }
            else {
                storages_[type] = std::static_pointer_cast<void>(std::make_shared<S>());
                return true;
            }
        }

        template <class R>
        bool register_resource(const R& initial_value) {
            auto type = Types::resource_type<R>();
            if(resources_.count(type) > 0) {
                return false;
            }
            else {
                resources_[type] = std::static_pointer_cast<void>(std::make_shared<R>());
                return true;
            }
        }

        //TODO: add Families
    };

}
