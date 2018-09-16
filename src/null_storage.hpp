//
// Created by Alex on 9/14/2018.
//

#pragma once

#include <vector>

#include "storage.hpp"

namespace apollo {
    template <class C>
    class NullStorage : public Storage<C> {
    private:
        std::vector<EGeneration> gens_;
        C null_value_;

    public:
        NullStorage() : gens_(), null_value_() {}

        bool add_for(const Entity& entity, C&& component) override {
            auto index = static_cast<size_t>(entity.index);

            if (index > gens_.size()) {
                gens_.resize(index + 1, NULL_GEN);
            }
            else if (gens_[index] == entity.generation) {
                return false;
            }

            gens_[index] = entity.generation;
            return true;
        }

        C* data() override {
            return NULL;
        }

        C const* read_data() const override {
            return NULL;
        }

        C& get_for(const Entity& entity) override {
            return null_value_;
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
            return null_value_;
        }

        bool remove_for(const Entity& entity) override {
            auto index = static_cast<size_t>(entity.index);
            if (index > gens_.size()) {
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

        void update() override {} //nothing to do
    };
}
