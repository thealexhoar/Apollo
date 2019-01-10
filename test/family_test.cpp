//
// Created by alex on 19/12/18.
//

#include "catch/catch.hpp"
#include "../src/apollo.hpp"

using namespace apollo;

static constexpr const char* tag = "[family]";

TEST_CASE("Empty Family can be contructed", tag) {
    auto family = Family();

    //empty family will match anything
    std::vector<bool> bits0 {};
    std::vector<bool> bits1 { false, false, false };
    std::vector<bool> bits2 { true, true, true };
    std::vector<bool> bits3 { true, false, false };
    std::vector<bool> bits4 { false, true, false, true };
    std::vector<bool> bits5 { false, true, true, false, true, true, false };

    REQUIRE(family.matches(bits0));
    REQUIRE(family.matches(bits1));
    REQUIRE(family.matches(bits2));
    REQUIRE(family.matches(bits3));
    REQUIRE(family.matches(bits4));
    REQUIRE(family.matches(bits5));
}

TEST_CASE("Family can match for ALL given types", tag) {
    auto family = Family().with_all_of<int, float, double>();

    std::vector<bool> bits0(0);
    REQUIRE(!family.matches(bits0));

    std::vector<bool> bits1(0);
    set_vector_bit(bits1, Types::component_type<int>());
    set_vector_bit(bits1, Types::component_type<float>());
    set_vector_bit(bits1, Types::component_type<double>());
    REQUIRE(family.matches(bits1));

    std::vector<bool> bits2(0);
    set_vector_bit(bits2, Types::component_type<int>());
    set_vector_bit(bits2, Types::component_type<float>());
    set_vector_bit(bits2, Types::component_type<double>());
    set_vector_bit(bits2, 10);
    REQUIRE(family.matches(bits2));

    std::vector<bool> bits3(0);
    set_vector_bit(bits3, Types::component_type<int>());
    set_vector_bit(bits3, Types::component_type<float>());
    REQUIRE(!family.matches(bits3));

}

TEST_CASE("Family can match for NONE of given types", tag) {
    auto family = Family().with_none_of<int, float, double>();

    std::vector<bool> bits0(0);
    REQUIRE(family.matches(bits0));

    std::vector<bool> bits1(0);
    set_vector_bit(bits1, Types::component_type<int>());
    set_vector_bit(bits1, Types::component_type<float>());
    set_vector_bit(bits1, Types::component_type<double>());
    REQUIRE(!family.matches(bits1));

    std::vector<bool> bits2(0);
    set_vector_bit(bits2, Types::component_type<int>());
    set_vector_bit(bits2, Types::component_type<float>());
    set_vector_bit(bits2, Types::component_type<double>());
    set_vector_bit(bits2, 10);
    REQUIRE(!family.matches(bits2));

    std::vector<bool> bits3(0);
    set_vector_bit(bits3, Types::component_type<int>());
    set_vector_bit(bits3, Types::component_type<float>());
    REQUIRE(!family.matches(bits3));

    std::vector<bool> bits4(0);
    set_vector_bit(bits4, Types::component_type<int>());
    REQUIRE(!family.matches(bits4));

    std::vector<bool> bits5(0);
    set_vector_bit(bits5, Types::component_type<float>());
    REQUIRE(!family.matches(bits5));

    std::vector<bool> bits6(0);
    set_vector_bit(bits6, Types::component_type<double>());
    REQUIRE(!family.matches(bits6));

    std::vector<bool> bits7(0);
    set_vector_bit(bits7, Types::component_type<long>());
    REQUIRE(family.matches(bits7));
}

TEST_CASE("Family can match for ONE of given types", tag) {
    auto family0 = Family().with_one_of<int, float, double>();

    auto family1 = Family()
        .with_one_of<int, double>()
        .with_one_of<float>();

    auto family2 = Family()
        .with_one_of<int>()
        .with_one_of<float>()
        .with_one_of<double>();

    std::vector<bool> bits0(0);
    REQUIRE(!family0.matches(bits0));
    REQUIRE(!family1.matches(bits0));
    REQUIRE(!family2.matches(bits0));

    std::vector<bool> bits1(0);
    set_vector_bit(bits1, Types::component_type<int>());
    set_vector_bit(bits1, Types::component_type<float>());
    set_vector_bit(bits1, Types::component_type<double>());
    REQUIRE(family0.matches(bits1));
    REQUIRE(family1.matches(bits1));
    REQUIRE(family2.matches(bits1));

    std::vector<bool> bits2(0);
    set_vector_bit(bits2, Types::component_type<int>());
    REQUIRE(family0.matches(bits2));
    REQUIRE(!family1.matches(bits2));
    REQUIRE(!family2.matches(bits2));

    std::vector<bool> bits3(0);
    set_vector_bit(bits3, Types::component_type<float>());
    REQUIRE(family0.matches(bits3));
    REQUIRE(!family1.matches(bits3));
    REQUIRE(!family2.matches(bits3));

    std::vector<bool> bits4(0);
    set_vector_bit(bits4, Types::component_type<int>());
    set_vector_bit(bits4, Types::component_type<long>());
    REQUIRE(family0.matches(bits4));
    REQUIRE(!family1.matches(bits4));
    REQUIRE(!family2.matches(bits4));

}