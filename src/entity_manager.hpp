 //
// Created by alex on 18/02/18.
//

#pragma once

#include <cinttypes>
#include <vector>

#include "entity.hpp"

namespace apollo {

    class EntityManager {
    private:
        EIndex next_index_ = 0;
        std::vector<Entity> recycled_entities_;

    public:
        EntityManager() :
            recycled_entities_()
        {}

        // recycled entities are reused in a stack-y way
        // IE first-in, last-out
        Entity create_entity() {
            if (!recycled_entities_.empty()) {
                Entity old = recycled_entities_[recycled_entities_.size()-1];
                recycled_entities_.pop_back();
                Entity out = Entity(old.index, old.generation + 1);
                return out;
            }
            else {
                Entity out = Entity(next_index_++, 1);
                return out;
            }
        }

        void recycle_entity(const Entity& entity) {
            recycled_entities_.push_back(entity);
        }

        EIndex next_index() {
            return next_index_;
        }

        size_t currently_recycled() {
            return recycled_entities_.size();
        }
    };
}