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
        std::vector<bool> one_bits;

        Family();
    };


    class FamilyBuilder {

    public:
        FamilyBuilder();

        Family build();

        FamilyBuilder& with_all(...);

        FamilyBuilder& with_none(...);

        FamilyBuilder& with_one(...);

    private:
        void with_all_helper(...);
        void with_none_helper(...);
        void with_one_helper(...);
    };

}