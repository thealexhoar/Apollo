/*
CREATED: 17/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>
#include <typeinfo>
#include <vector>

#include "component.hpp"
#include "entity.hpp"

namespace apollo {

    class ComponentArray {
    private:
        std::vector<uint8_t> _bytes;
        size_t _component_hash;
        size_t _component_size;

    public:
        template <class T>
        ComponentArray(bool check_safety = true);

        ~ComponentArray();

        size_t size() const;

        template <class T>
        T* get(const Entity& entity);

        template <class T>
        T const* get(const Entity& entity) const;

        void erase_at(size_t position);

        template <class T>
        T* get_data();

        template <class T>
        T const* get_data() const;

        template <class T>
        void set(const Entity& entity, const T& component);
    };

}