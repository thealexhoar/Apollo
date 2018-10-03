//
// Created by Alex on 9/14/2018.
//

#pragma once

#include <bitset>
#include <stdio.h>

#include "types.hpp"

namespace apollo {

    struct Family {
        std::vector<bool> all_bits;
        std::vector<bool> none_bits;

        Family() : all_bits(), none_bits() {}
    };


    //TODO: finish implementing
    class FamilyBuilder {

    public:
        FamilyBuilder() {}

        Family build() {
            return Family();
        }

        template <typename C>
        FamilyBuilder& with() {
            ComponentType type = Types::component_type<C>();

            return *this;
        }

        template <typename C>
        FamilyBuilder& without() {
            ComponentType type = Types::component_type<C>();

            return *this;
        }
    };

}