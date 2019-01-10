//
// Created by Alex on 9/14/2018.
//

#pragma once

#include <stdio.h>

#include "types.hpp"
#include "vector_bit_ops.hpp"

namespace apollo {

    typedef size_t FamilyID;

    class Family {
    private:
        std::vector<bool> all_bits_;
        std::vector<std::vector<bool>> one_bits_;
        std::vector<bool> none_bits_;

        template <typename C>
        Family& with_one_of_helper(std::vector<bool> bits) {
            ComponentType type = Types::component_type<C>();
            set_vector_bit(bits, static_cast<size_t>(type));
            one_bits_.push_back(bits);
            return *this;
        }

        template <typename C0, typename C1, typename... Args>
        Family& with_one_of_helper(std::vector<bool> bits) {
            ComponentType type = Types::component_type<C0>();
            set_vector_bit(bits, static_cast<size_t>(type));
            return with_one_of_helper<C1, Args...>(bits);
        }

    public:
        Family() : all_bits_(), one_bits_(), none_bits_() {}

        Family(const Family& other) :
            all_bits_(other.all_bits_),
            one_bits_(other.one_bits_),
            none_bits_(other.none_bits_)
        {}

        template <typename C>
        Family& with_all_of() {
            ComponentType type = Types::component_type<C>();
            set_vector_bit(all_bits_, static_cast<size_t>(type));
            return *this;
        }

        template <typename C0, typename C1, typename... Args>
        Family& with_all_of() {
            ComponentType type = Types::component_type<C0>();
            set_vector_bit(all_bits_, static_cast<size_t>(type));
            return with_all_of<C1, Args...>();
        }

        template <typename C>
        Family& with_one_of() {
            return with_one_of_helper<C>(std::vector<bool>());
        }

        template <typename C0, typename C1, typename... Args>
        Family& with_one_of() {
            return with_one_of_helper<C0, C1, Args...>(std::vector<bool>());
        }

        template <typename C>
        Family& with_none_of() {
            ComponentType type = Types::component_type<C>();
            set_vector_bit(none_bits_, static_cast<size_t>(type));
            return *this;
        }

        template <typename C0, typename C1, typename... Args>
        Family& with_none_of() {
            ComponentType type = Types::component_type<C0>();
            set_vector_bit(none_bits_, static_cast<size_t>(type));
            return with_none_of<C1, Args...>();
        }

        bool matches(const std::vector<bool>& bits) const {
            if (!vector_check_all(all_bits_, bits)) {
                return false;
            }
            for (auto& one_bits : one_bits_) {
                if (!vector_check_one(one_bits, bits)) {
                    return false;
                }
            }
            if (vector_check_one(none_bits_, bits)) {
                return false;
            }

            return true;
        }
    };

}