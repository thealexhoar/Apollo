//
// Created by alex on 25/01/18.
//

#include "catch/catch.hpp"
#include "../src/apollo.hpp"
#include "test_components.hpp"

#include <iostream>

TEST_CASE("ComponentArray works", "[component_array]") {
    class A {
        int i = 0;
    };
    auto a = A();
    auto tc8 = TestComponent4(0);
    auto tc16 = TestComponent8(1,2);

    std::cout << sizeof(a) << '\n';
    std::cout << sizeof(tc8) << '\n';
    std::cout << sizeof(tc16) << '\n';
}

