//
// Created by alex on 25/01/18.
//

#pragma once

#include <memory>

#include "entity.hpp"

namespace apollo {

    template <class C>
    class ReadIterator {
        virtual const C& get() const = 0;
        virtual Entity get_entity() const = 0;
        virtual bool iterate() = 0;
    };

    template <class C>
    class WriteIterator {
        virtual C& get() const = 0;
        virtual Entity get_entity() const = 0;
        virtual bool iterate() = 0;
    };

    template <class C>
    class Storage {
    public:
        virtual bool add_for(const Entity& entity, const C& component) = 0;
        virtual C& get_for(const Entity& entity) = 0;
        virtual const C& get_for(const Entity& entity) const = 0;
        virtual std::shared_ptr<ReadIterator<C>> get_read_iterator() const = 0;
        virtual std::shared_ptr<WriteIterator<C>> get_write_iterator() = 0;
        virtual bool has_for(const Entity& entity) const = 0;
        virtual bool remove_for(const Entity& entity) = 0;
        virtual void update() = 0;
    };

}