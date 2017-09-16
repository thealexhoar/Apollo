/*
CREATED: 16/09/17
NOTES: 
*/

#pragma once

#include <set>

#include "types.hpp"

namespace apollo {

    class ResourceSubscription {
    private:
        std::set<ComponentType> _read_components;
        std::set<ComponentType> _write_components;
        std::set<ResourceType> _read_resources;
        std::set<ResourceType> _write_resources;

    public:
        ResourceSubscription();
        ~ResourceSubscription();

        ResourceSubscription& add_read_component(const ComponentType& type);

        ResourceSubscription& add_write_component(const ComponentType& type);

        ResourceSubscription& add_read_resource(const ResourceType& type);

        ResourceSubscription& add_write_resource(const ResourceType& type);
    };

}