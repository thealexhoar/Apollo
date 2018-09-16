//
// Created by Alex on 9/14/2018.
//

#pragma once

#include <stdio.h>
#include <vector>

#include <bits/unordered_set.h>
#include "entity.hpp"
#include "storage.hpp"

namespace apollo {
    template <class C>
    class VecStorage : public Storage<C> {
    private:
        std::vector<C> data_;
        std::vector<EGeneration> gens_;

    public:
        VecStorage() : data_(), gens_() {
            printf("default constructa \n");
        }

        bool add_for(const Entity& entity, C&& component) override {
            auto index = static_cast<size_t>(entity.index);

            if (index >= data_.size()) {
                data_.resize(index + 1);
                gens_.resize(index + 1);
            }
            else if (gens_[index] != NULL_GEN) {
                return false;
            }

            data_[index] = component;
            gens_[index] = entity.generation;

            return true;
        }

        C* data() override {
            return data_.data();
        }

        C const* read_data() const override {
            return data_.data();
        }

        C& get_for(const Entity& entity) override {
            auto index = static_cast<size_t>(entity.index);
            return data_[index];
        }

        bool has_for(const Entity& entity) override {
            auto index = static_cast<size_t>(entity.index);
            if (index > gens_.size()) {
                return false;
            }
            else {
                return gens_[index] == entity.generation;
            }
        }

        const C& read_for(const Entity& entity) const override {
            auto index = static_cast<size_t>(entity.index);
            return data_[index];
        }

        bool remove_for(const Entity& entity) override {
            auto index = static_cast<size_t>(entity.index);
            if (index > data_.size()) {
                return false;
            }
            else if (gens_[index] != entity.generation) {
                return false;
            }
            else {
                gens_[index] = NULL_GEN;
                return true;
            }
        }

        void update() override {} // nothing to update
    };

}
