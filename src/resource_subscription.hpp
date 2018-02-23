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
        std::unordered_set<ComponentType> _read_components;
        std::unordered_set<ComponentType> _write_components;
        std::unordered_set<ResourceType> _read_resources;
        std::unordered_set<ResourceType> _write_resources;

    public:
        ResourceSubscription() :
            _read_components(),
            _write_components(),
            _read_resources(),
            _write_resources()
        {}

        ResourceSubscription& add_read_component(const ComponentType& type) {
            if (_write_components.count(type) == 0) {
                _read_components.insert(type);
            }
            return *this;
        }

        ResourceSubscription& add_write_component(const ComponentType& type) {
            _write_components.insert(type);
            if (_read_components.count(type) > 0) {
                _read_components.erase(type);
            }
            return *this;
        }

        ResourceSubscription& add_read_resource(const ResourceType& type) {
            if (_write_resources.count(type) == 0) {
                _read_resources.insert(type);
            }
            return *this;
        }

        ResourceSubscription& add_write_resource(const ResourceType& type) {
            _write_resources.insert(type);
            if (_read_resources.count(type) > 0) {
                _read_resources.erase(type);
            }
            return *this;
        }
    };

}