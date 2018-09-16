/*
CREATED: 19/09/17
NOTES:
*/
#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include <iostream>

#include "../src/apollo.hpp"
#include "../src/family.hpp"

//this file is primarily just to ensure CATCH_CONFIG_MAIN is defined
TEST_CASE("Initializing tests for Apollo!", "[main]") {
    apollo::VecStorage<int> v{};
    auto s = static_cast<apollo::Storage<int>*>(&v);
    s->add_for(apollo::Entity(0, 0), 0);

    TEST(1, 2, 3, 4);

    apollo::FamilyBuilder().with_all(1, 2, 3);
}