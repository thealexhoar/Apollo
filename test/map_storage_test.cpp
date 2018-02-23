//
// Created by alex on 18/02/18.
//

#include "catch/catch.hpp"
#include "../../apollo/src/map_storage.hpp"
#include "test_components.hpp"

using namespace apollo;

static constexpr const char* tag = "[map_storage]";

TEST_CASE("MapStorage can be constructed", tag) {
    MapStorage<TestComponent8> ms = MapStorage<TestComponent8>();
    //REQUIRE(1 == 1);
}