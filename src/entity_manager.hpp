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
        EIndex latest_index = 0;
        std::vector<Entity> recycled_entities_;
    public:
        EntityManager() :
            recycled_entities_()
        {}

        Entity create_entity() {
            if (!recycled_entities_.empty()) {
                Entity old = *recycled_entities_.end();
                recycled_entities_.pop_back();
                Entity out = Entity(old.index, old.generation + 1);
                return out;
            }
            else {
                Entity out = Entity(latest_index++, 1);
                return out;
            }
        }

        void recycle_entity(const Entity& entity) {
            recycled_entities_.push_back(entity);
        }
    };
}