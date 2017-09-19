/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>
#include <vector>

#include "component.hpp"
#include "component_storage.hpp"
#include "entity.hpp"

namespace apollo {

    class ComponentArray : public ComponentStorage {
    protected:
        std::vector<uint8_t> _bytes;
        size_t _component_size, _current_size;

    protected:
        ComponentArray(size_t initial_capacity, size_t size);

    public:
        ~ComponentArray();

        template <class T>
        static ComponentArray new_for_type(size_t initial_capacity);

        bool add_for(const Entity& entity, const Component& component) override;

        bool remove_for(const Entity& entity) override;
    };
}