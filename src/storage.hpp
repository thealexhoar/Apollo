//
// Created by alex on 25/01/18.
//

#pragma once

#include <memory>

#include "entity.hpp"

namespace apollo {
    class GenericStorage {
    public:
        virtual bool has_for(const Entity& entity) = 0;
        virtual bool remove_for(const Entity& entity) = 0;
        virtual void update() = 0;
    };

    template <class C>
    class Storage : public GenericStorage {
    public:
        virtual bool add_for(const Entity& entity, C&& component) = 0;
        virtual C* data() = 0;
        virtual C const* read_data() const = 0;
        virtual C& get_for(const Entity& entity) = 0;
        virtual const C& read_for(const Entity& entity) const = 0;
    };
}