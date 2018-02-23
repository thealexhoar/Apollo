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
        EIndex _latest_index = 0;
        std::vector<Entity> _recycled_entities;
    public:
        EntityManager() :
            _recycled_entities()
        {}

        Entity create() {
            if (_recycled_entities.size() > 0) {
                Entity old = *_recycled_entities.end();
                _recycled_entities.pop_back();
                Entity out = Entity(old.index, old.generation+1);
                return out;
            }
            else {
                Entity out = Entity(_latest_index++, 1);
                return out;
            }
        }

        void recycle(const Entity& entity) {
            _recycled_entities.push_back(entity);
        }
    };
}