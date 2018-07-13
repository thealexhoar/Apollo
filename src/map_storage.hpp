//
// Created by alex on 18/02/18.
//

#pragma once

#include <type_traits>
#include <unordered_map>
#include <unordered_set>

#include "entity.hpp"
#include "storage.hpp"

namespace apollo {
    template<class C>
    class MapStorage : public Storage<C> {

    private:
        std::unordered_map<EIndex, C> data_;
        std::unordered_set<Entity, EntityHash> entities_;

    public:

        MapStorage() : data_(), entities_() {}

        bool add_for(const Entity& entity, const C& component) override {
            const C &datum = static_cast<const C &>(component);
            if (data_.count(entity.index) > 0) {
                return false;
            } else {
                data_.insert(std::make_pair(entity.index, datum));
                entities_.insert(entity);
                return true;
            }
        }

        C& get_for(const Entity& entity) override {
            return data_.at(entity.index);
        }

        const C& get_for(const Entity& entity) const override {
            return data_.at(entity.index);
        }

        bool has_for(const Entity &entity) const override {
            return entities_.count(entity) > 0;
        }

        bool remove_for(const Entity &entity) override {
            if (entities_.count(entity) == 0) {
                return false;
            } else {
                entities_.erase(entity);
                data_.erase(entity.index);
                return true;
            }
        }

        void update() override {}
    };
}

