//
// Created by alex on 18/02/18.
//

#pragma once

#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <assert.h>

#include "entity.hpp"
#include "storage.hpp"

namespace apollo {
    template<class C>
    class MapStorage : public Storage<C> {

    private:
        std::vector<C> data_;
        std::unordered_map<EIndex, size_t> data_mappings_;
        std::unordered_set<Entity, EntityHash> entities_;

    public:

        MapStorage() : data_(), data_mappings_(), entities_() {}

        bool add_for(const Entity& entity, C&& component) override {
            if (entities_.count(entity) > 0) {
                return false;
            }

            if (data_mappings_.count(entity.index) > 0) {
                data_[data_mappings_[entity.index]] = component;
            }
            else {
                data_mappings_[entity.index] = data_.size();
                data_.push_back(component);
            }

            return true;
        }

        C& get_for(const Entity& entity) override {
            assert(data_mappings_.count(entity.index) > 0);
            auto index = data_mappings_.at(entity.index);
            assert(data_.size() > index);
            return data_[index];
        }

        bool has_for(const Entity& entity) override {
            return entities_.count(entity) > 0;
        }

        const C& read_for(const Entity& entity) const override {
            assert(data_mappings_.count(entity.index) > 0);
            auto index = data_mappings_.at(entity.index);
            assert(data_.size() > index);
            return data_[index];
        }

        bool remove_for(const Entity& entity) override {
            if (entities_.count(entity) == 0) {
                return false;
            }

            entities_.erase(entity);
            return true;
        }

        void update() override {}
    };
}

