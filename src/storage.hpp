//
// Created by alex on 25/01/18.
//

#pragma once

#include "entity.hpp"

namespace apollo {
    class Storage {
        virtual void* get_iterator() = 0;
        virtual void const* read_iterator() = 0;
        virtual void* get_for(const Entity& entity) = 0;
        virtual void const* read_for(const Entity& entity) = 0;
        virtual bool has_for(const Entity& entity) = 0;
    };
}