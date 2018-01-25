/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>
#include <unordered_map>
#include <vector>

#include "entity.hpp"
#include "resource_accessor.hpp"

namespace apollo {
    class ResourceAccessor;

    class ComponentArray {
    private:
        std::vector<uint8_t> _bytes;
        size_t _component_size, _current_size;
        int (*_comparison)(void*, void*, ResourceAccessor*);
        std::unordered_map<Entity, void*> _data_lookup;
        std::unordered_map<void*, Entity> _reverse_data_lookup;

    public:
        ComponentArray(
                size_t initial_capacity,
                size_t size,
                int (*comparison)(void*, void*, ResourceAccessor*)
        );
        ComponentArray(size_t initial_capacity, size_t size);
        ~ComponentArray();

        template <class T>
        static ComponentArray* new_for_type(size_t initial_capacity);

        template <class T>
        static ComponentArray* new_for_type(
                size_t initial_capacity,
                int (*comparison)(void*, void*, ResourceAccessor*)
        );

        void* get_data() {
            return reinterpret_cast<void*>(_bytes.data());
        }

        void const* get_data() const {
            return reinterpret_cast<void const*>(_bytes.data());
        }

        void* get_for(const Entity& entity) {
            return _data_lookup.at(entity);
        }

        void const* get_for(const Entity& entity) const {
            return _data_lookup.at(entity);
        }

        size_t size() const {
            return _current_size / _component_size;
        }

        bool has_for(const Entity& entity) const {
            return _data_lookup.count(entity) > 0;
        }

        bool add_for(const Entity& entity, void const* component);

        bool remove_for(const Entity& entity);

        void sort(ResourceAccessor* resource_accessor);

    private:
        void swap(void* c1, void* c2);
    };
}