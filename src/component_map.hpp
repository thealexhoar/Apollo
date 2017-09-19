/*
CREATED: 19/09/17
NOTES: 
*/

#pragma once

#include <cinttypes>


#include "component_storage.hpp"

namespace apollo {
    class ComponentMap : public ComponentStorage {
    protected:
        size_t _component_size;

    protected:
        ComponentMap(size_t size);

    public:
        ~ComponentMap();

        template <class T>
        static ComponentMap new_for_type();

        bool add_for(const Entity& entity, const Component& component) override;

        bool remove_for(const Entity& entity) override;
    };
}