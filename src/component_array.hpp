/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>
#include <unordered_map>
#include <vector>

#include "component.hpp"
#include "entity.hpp"
#include "resource_accessor.hpp"

namespace apollo {
    class ResourceAccessor;

    class ComponentArray {
    private:
        std::vector<uint8_t> _bytes;
        size_t _component_size, _current_size;
        int (*_comparison)(Component*, Component*, ResourceAccessor*);
        std::unordered_map<Entity, Component*> _data_lookup;
        std::unordered_map<Component*, Entity> _reverse_data_lookup;

    public:
        ComponentArray(
                size_t initial_capacity,
                size_t size,
                int (*comparison)(Component*, Component*, ResourceAccessor*)
        );
        ComponentArray(size_t initial_capacity, size_t size);
        ~ComponentArray();

        template <class T>
        static ComponentArray* new_for_type(size_t initial_capacity);

        template <class T>
        static ComponentArray* new_for_type(
                size_t initial_capacity,
                int (*comparison)(Component*, Component*, ResourceAccessor*)
        );

        Component* get_data() {
            return reinterpret_cast<Component*>(_bytes.data());
        }

        Component const* get_data() const {
            return reinterpret_cast<Component const*>(_bytes.data());
        }

        Component* get_for(const Entity& entity) {
            return _data_lookup.at(entity);
        }

        Component const* get_for(const Entity& entity) const {
            return _data_lookup.at(entity);
        }

        bool has_for(const Entity& entity) const {
            return _data_lookup.count(entity) > 0;
        }

        bool add_for(const Entity& entity, const Component& component);

        bool remove_for(const Entity& entity);

        void sort(ResourceAccessor* resource_accessor);

    private:
        void swap(Component* c1, Component* c2);
    };
}