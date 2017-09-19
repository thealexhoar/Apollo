/*
CREATED: 18/09/17
NOTES: 
*/

#pragma once

#include <cstdlib>
#include <cinttypes>
#include <unordered_map> //faster than std::map, at the expense of memory

#include "component.hpp"
#include "entity.hpp"

namespace apollo {

    class ComponentStorage {
    protected:
        std::unordered_map<Entity, Component*> _data_lookup;

        ComponentStorage() : _data_lookup() {}
    public:
        Component* get_for(const Entity& entity) {
            return _data_lookup.at(entity);
        }

        Component const* get_for(const Entity& entity) const {
            return _data_lookup.at(entity);
        }

        bool has_for(const Entity& entity) const {
            return _data_lookup.count(entity) > 0;
        }

        virtual bool add_for(const Entity& entity, const Component& component) = 0;

        virtual bool remove_for(const Entity& entity) = 0;
    };
}