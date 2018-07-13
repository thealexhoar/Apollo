/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include <unordered_set>

#include "types.hpp"

namespace apollo {

    class World;

    class ResourceSubscription {
        friend class World;
    private:
        std::unordered_set<ComponentType> read_components_;
        std::unordered_set<ComponentType> write_components_;
        std::unordered_set<ResourceType> read_resources_;
        std::unordered_set<ResourceType> write_resources_;

    public:
        ResourceSubscription() :
            read_components_(),
            write_components_(),
            read_resources_(),
            write_resources_()
        {}

        ResourceSubscription& with_read_storage(const ComponentType &type) {
            if (write_components_.count(type) == 0) {
                read_components_.insert(type);
            }
            return *this;
        }

        ResourceSubscription& with_write_storage(const ComponentType& type) {
            write_components_.insert(type);
            if (read_components_.count(type) > 0) {
                read_components_.erase(type);
            }
            return *this;
        }

        ResourceSubscription& with_read_resource(const ResourceType& type) {
            if (write_resources_.count(type) == 0) {
                read_resources_.insert(type);
            }
            return *this;
        }

        ResourceSubscription& with_write_resource(const ResourceType& type) {
            write_resources_.insert(type);
            if (read_resources_.count(type) > 0) {
                read_resources_.erase(type);
            }
            return *this;
        }
    };

}