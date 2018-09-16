//
// Created by Alex on 9/14/2018.
//

#include <cstdarg>
#include "family.hpp"

namespace apollo {

    Family::Family() {}

    FamilyBuilder::FamilyBuilder() {}

    Family FamilyBuilder::build() {}

    FamilyBuilder& FamilyBuilder::with_all(...) {
        with_all_helper(c_types, -1);
        return *this;
    }

    FamilyBuilder& FamilyBuilder::with_none(...) {
        with_none_helper(c_types, -1);
        return *this;
    }

    FamilyBuilder& FamilyBuilder::with_one(...) {
        with_one_helper(c_types, -1);
        return *this;
    }

    void FamilyBuilder::with_all_helper(...) {
        va_list args;
        va_start(args, c_types);
    }

    void FamilyBuilder::with_none_helper(...) {}

    void FamilyBuilder::with_one_helper(...) {}
}