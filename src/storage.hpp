//
// Created by alex on 25/01/18.
//

#pragma once

#include <memory>

#include "entity.hpp"

namespace apollo {

    template <class T>
    class ReadIterator {
        virtual const T& get() const = 0;
        virtual Entity get_entity() const = 0;
        virtual bool iterate() = 0;
    };

    template <class T>
    class WriteIterator {
        virtual T& get() const = 0;
        virtual Entity get_entity() const = 0;
        virtual bool iterate() = 0;
    };

    template <class T>
    class Storage {
    public:
        virtual bool add_for(const Entity& entity, const T& component) = 0;
        virtual T& get_for(const Entity& entity) = 0;
        virtual const T& get_for(const Entity& entity) const = 0;
        virtual std::shared_ptr<ReadIterator<T>> get_read_iterator() const = 0;
        virtual std::shared_ptr<WriteIterator<T>> get_write_iterator() = 0;
        virtual bool has_for(const Entity& entity) const = 0;
        virtual bool remove_for(const Entity& entity) = 0;
        virtual void update() = 0;
    };

}