//
// Created by alex on 25/01/18.
//

#pragma once

#include <memory>

#include "entity.hpp"

namespace apollo {
    template <class C>
    class Storage {
    public:
        virtual bool add_for(const Entity& entity, const C& component) = 0;
        virtual C& get_for(const Entity& entity) = 0;
        virtual const C& get_for(const Entity& entity) const = 0;
        virtual bool has_for(const Entity& entity) const = 0;
        virtual bool remove_for(const Entity& entity) = 0;
        virtual void update() = 0;
    };
}